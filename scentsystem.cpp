#include "scentsystem.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "simulation.h"

ScentSystem::ScentSystem(Simulation* pSimulation)
	: mSimulation(pSimulation),
	  mThreshhold(0.1),
	  mScentMap(coordMap()),
	  mAdditionQueue(coordMap()),
	  mSubtractionQueue(coordMap()),
	  mDiffusivity(0.15),
	  mDecayRate(0.8) {}

ScentSystem::~ScentSystem() {}

void ScentSystem::add(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		pCoordMap.emplace(pCoords, pAmount);
	else
		pCoordMap.at(pCoords) += pAmount;
	pCoordMap.at(pCoords) = std::min<qreal>(pCoordMap.at(pCoords), 1);
}

void ScentSystem::subtract(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		return;
	pCoordMap.at(pCoords) -= pAmount;
	pCoordMap.at(pCoords) = std::max<qreal>(pCoordMap.at(pCoords), 0);
}

void ScentSystem::diffuse()
{
	for (auto it1 = mScentMap.begin(); it1 != mScentMap.end(); it1++)
	{
		coordPair curCell = it1->first;
		qreal adjScentWeightedSum = 0;
		int offset = -1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int m = curCell.first + i + offset;
				int n = curCell.second + j + offset;
				if (m >= mSimulation->board()->columns()
					|| m < 0
					|| n >= mSimulation->board()->rows()
					|| n < 0
					|| i + offset == 0 && j + offset == 0)
				{
					continue;
				}

				coordPair adjCell(m, n);
				qreal curScent = mScentMap.at(curCell);
				qreal adjScent = mScentMap.count(adjCell) ? mScentMap.at(adjCell) : 0;

				qreal distance = std::sqrt(pow(i + offset, 2) + pow(j + offset, 2));

				qreal transfer = std::max<qreal>((curScent - adjScent) * mDiffusivity / distance, 0);
				adjScentWeightedSum += (transfer + adjScent) / distance;

				add(mAdditionQueue, adjCell, transfer);
			}
		}

		qreal adjScentWeightedAverage = adjScentWeightedSum / 8.0;
		qreal outFlow = (mScentMap.at(curCell) - adjScentWeightedAverage) * mDiffusivity / ((4 + 4 * sqrt(2)) / 8);
		outFlow += std::max(mScentMap.at(curCell) * mDecayRate, 10 * mThreshhold);
		subtract(mSubtractionQueue, curCell, outFlow);
	}

	for (auto it2 = mAdditionQueue.begin(); it2 != mAdditionQueue.end(); it2++)
	{
		coordPair coords = it2->first;
		add(mScentMap, coords, mAdditionQueue.at(coords));
	}
	mAdditionQueue.clear();

	for (auto it2 = mSubtractionQueue.begin(); it2 != mSubtractionQueue.end(); it2++)
	{
		coordPair coords = it2->first;
		subtract(mScentMap, coords, mSubtractionQueue.at(coords));
	}
	mSubtractionQueue.clear();

	for (auto it2 = mScentMap.begin(); it2 != mScentMap.end();)
	{
		coordPair coords = it2->first;
		// Standard associative-container erase idiom: 
		// https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it
		if (mScentMap.at(coords) < mThreshhold)
		{
			mScentMap.erase(it2++);
		}
		else
		{
			it2++;
		}
	}
}

coordMap& ScentSystem::scentMap()
{
	return mScentMap;
}

qreal ScentSystem::getScent(coordPair pCoords)
{
	return mScentMap.count(pCoords) ? mScentMap.at(pCoords) : 0;
}
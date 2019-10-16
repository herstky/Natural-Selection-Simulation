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
	  diffusivity(0.15) {}

ScentSystem::~ScentSystem() {}

void ScentSystem::add(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		pCoordMap.emplace(pCoords, pAmount);
	else
		pCoordMap[pCoords] += pAmount;
	pCoordMap[pCoords] = std::min<qreal>(pCoordMap[pCoords], 1);
}

void ScentSystem::subtract(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		return;
	pCoordMap[pCoords] -= pAmount;
	pCoordMap[pCoords] = std::max<qreal>(pCoordMap[pCoords], 0);
}

void ScentSystem::diffuse()
{
	for (auto it = mScentMap.begin(); it != mScentMap.end(); it++)
	{
		int size = mScentMap.size();
		coordPair curCell = it->first;
		qreal totalOut = 0;
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
					|| n < 0)
				{
					continue;
				}

				coordPair adjCell(m, n);
				qreal curScent = mScentMap[curCell];
				qreal adjScent = mScentMap.count(adjCell) ? mScentMap[adjCell] : 0;

				qreal distance = std::sqrt(pow(i, 2) + pow(j, 2));

				qreal transfer = std::max<qreal>((curScent - adjScent) * diffusivity / distance, 0);
				totalOut += transfer;

				add(mAdditionQueue, adjCell, transfer);
			}
		}

		totalOut += 2.0 * mScentMap[curCell] * diffusivity;
		subtract(mSubtractionQueue, curCell, totalOut);
	}

	for (auto it = mAdditionQueue.begin(); it != mAdditionQueue.end(); it++)
	{
		coordPair coords = it->first;
		add(mScentMap, coords, mAdditionQueue[coords]);
	}
	mAdditionQueue.clear();

	for (auto it = mSubtractionQueue.begin(); it != mSubtractionQueue.end(); it++)
	{
		coordPair coords = it->first;
		subtract(mScentMap, coords, mSubtractionQueue[coords]);
	}
	mSubtractionQueue.clear();

	for (auto it = mScentMap.begin(); it != mScentMap.end();)
	{
		coordPair coords = it->first;
		// Standard associative-container erase idiom: 
		// https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it
		if (mScentMap[coords] < mThreshhold)
		{
			mScentMap.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

coordMap& ScentSystem::scentMap()
{
	return mScentMap;
}

qreal ScentSystem::getScent(coordPair pCoords)
{
	return mScentMap.count(pCoords) ? mScentMap[pCoords] : 0;
}
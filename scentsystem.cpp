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
		unsigned int size = mScentMap.size();
		std::pair<int, int> curCell = it->first;
		std::vector<std::pair<int, int>> directions
		{
			std::make_pair(-1, 0),
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
		};

		qreal totalOut = 0;
		for (auto direction : directions)
		{
			int col = it->first.second;
			int row = it->first.first;
			int colOffset = direction.second;
			int rowOffset = direction.first;
			std::pair<int, int> adjCell = std::make_pair(col + colOffset, row + rowOffset);
			if (adjCell.second >= mSimulation->getBoard()->columns()
				|| adjCell.second < 0
				|| adjCell.first >= mSimulation->getBoard()->rows()
				|| adjCell.first < 0)
			{
				continue;
			}

			qreal curScent = mScentMap[curCell];
			qreal adjScent = mScentMap.count(adjCell) ? mScentMap[adjCell] : 0;

			qreal transfer = std::max<qreal>((curScent - adjScent) * diffusivity, 0);
			totalOut += transfer;

			add(mAdditionQueue, adjCell, transfer);
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

	for (auto it = mScentMap.begin(); it != mScentMap.end(); it++)
	{
		coordPair coords = it->first;
		if (mScentMap[coords] < mThreshhold)
		{
			mScentMap.erase(it--);
		}
	}
}

coordMap& ScentSystem::scentMap()
{
	return mScentMap;
}
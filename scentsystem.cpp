#include "scentsystem.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "simulation.h"

ScentSystem::ScentSystem(Simulation* pSimulation)
	: mSimulation(pSimulation),
	  mThreshhold(0.005),
	  mScentMap(coordMap()),
	  mAdditionQueue(coordMap()),
	  mSubtractionQueue(coordMap()),
	  mDiffusivity(0.50),
	  mDecayRate(0.5) {}

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

void ScentSystem::update()
{
	for (auto it1 = mScentMap.begin(); it1 != mScentMap.end(); it1++)
	{
		coordPair curCell = it1->first;
		subtract(mSubtractionQueue, curCell, mDecayRate * mScentMap.at(curCell));
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

qreal ScentSystem::getThreshhold()
{
	return mThreshhold;
}

qreal ScentSystem::getDiffusivity()
{
	return mDiffusivity;
}
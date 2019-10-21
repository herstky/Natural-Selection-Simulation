#include "scentsystem.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "simulation.h"

ScentSystem::ScentSystem(Simulation& pSimulation)
	: mSimulation(pSimulation),
	  mThreshhold(0.01),
	  mScentMap(coordMap()),
	  mAdditionQueue(coordMap()),
	  mSubtractionQueue(coordMap()),
	  mDiffusivity(0.50),
	  mDecayRate(0.0) 
{
	qreal scentStrength = -1;
	int range = scentStrength * mDiffusivity / mThreshhold;
	for (int i = 0; i < pSimulation.board().columns(); i++)
	{
		for (int j = 0; j < range; j++)
		{
			mScentMap[coordPair(j, i)] = scentStrength * mDiffusivity / (1 - j / range);
			mScentMap[coordPair(pSimulation.board().rows() - 1 - j, i)] = scentStrength * mDiffusivity / (1 - j / range);
		}
	}
	for (int i = 0; i < pSimulation.board().rows(); i++)
	{
		for (int j = 0; j < range; j++)
		{
			mScentMap[coordPair(i,j)] = scentStrength * mDiffusivity / (1 - j / range);
			mScentMap[coordPair(i, pSimulation.board().columns() - 1 - j)] = scentStrength * mDiffusivity / (1 - j / range);
		}
	}
}

void ScentSystem::add(coordMap pCoordMap, coordPair pCoords, qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		pCoordMap[pCoords] = pAmount;
	else
		pCoordMap.at(pCoords) += pAmount;
	pCoordMap.at(pCoords) = std::min<qreal>(pCoordMap.at(pCoords), 1);
}

void ScentSystem::subtract(coordMap pCoordMap, coordPair pCoords, qreal pAmount)
{
	if (pCoordMap.count(pCoords) == 0)
		return;
	pCoordMap.at(pCoords) -= pAmount;
	pCoordMap.at(pCoords) = std::max<qreal>(pCoordMap.at(pCoords), 0);
}

void ScentSystem::update()
{
	for (auto i = mScentMap.begin(); i != mScentMap.end(); i++)
	{
		coordPair curCell = i->first;
		subtract(mSubtractionQueue, curCell, mDecayRate * mScentMap.at(curCell));
	}

	for (auto i = mAdditionQueue.begin(); i != mAdditionQueue.end(); i++)
	{
		coordPair coords = i->first;
		qreal scentStrength = i->second;
		emanateScent(coords, scentStrength);
	}
	mAdditionQueue.clear();

	for (auto i = mSubtractionQueue.begin(); i != mSubtractionQueue.end(); i++)
	{
		coordPair coords = i->first;
		subtract(mScentMap, coords, mSubtractionQueue.at(coords));
	}
	mSubtractionQueue.clear();

	for (auto i = mScentMap.begin(); i != mScentMap.end();)
	{
		coordPair coords = i->first;
		// Standard associative-container erase idiom: 
		// https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it
		if (mScentMap.at(coords) < mThreshhold)
		{
			mScentMap.erase(i++);
		}
		else
		{
			i++;
		}
	}
}

void ScentSystem::emanateScent(coordPair pCoords, qreal pScentStrength)
{
	int range = pScentStrength * mDiffusivity / mThreshhold;
	int offset = -(range / 2);
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			coordPair curCoords = coordPair(pCoords.first + i + offset, pCoords.second + j + offset);
			qreal distance = std::sqrt(pow(i + offset, 2) + pow(j + offset, 2));
			qreal intensity = distance ? pScentStrength * mDiffusivity / distance : pScentStrength;
			qreal curScent = mScentMap.count(curCoords) ? mScentMap.at(curCoords) : 0;
			curScent = std::max(intensity, curScent);
			if (curScent > mThreshhold)
				mScentMap[curCoords] = curScent;
		}
	}
}

coordMap ScentSystem::scentMap()
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

void ScentSystem::reset()
{
	mScentMap.clear();
	mAdditionQueue.clear();
	mSubtractionQueue.clear();
}
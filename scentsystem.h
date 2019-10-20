#pragma once

#include <unordered_map>
#include <string>
#include <utility>

#include "utils.h"
#include "board.h"

using coordPair = std::pair<int, int>;
using coordMap = std::unordered_map<coordPair, qreal, pair_hash>;

class Simulation;

class ScentSystem
{
public:
	friend Simulation;

	ScentSystem(Simulation& pSimulation);

	void add(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount);
	void subtract(coordMap& pCoordMap, const coordPair& pCoords, const qreal pAmount);
	void update();
	void emanateScent(coordPair& pCoords, qreal& pScentStrength);
	coordMap& scentMap();
	qreal getScent(coordPair& pCoords);
	qreal getThreshhold();
	qreal getDiffusivity();
	void reset();

private:
	Simulation& mSimulation;
	qreal mThreshhold;
	coordMap mScentMap;
	coordMap mAdditionQueue;
	coordMap mSubtractionQueue;
	qreal mDiffusivity; // needs to be tuned
	qreal mDecayRate;
};

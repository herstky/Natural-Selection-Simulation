#pragma once

#include <unordered_map>
#include <string>
#include <utility>

#include "utils.h"
#include "board.h"

// TODO: ScentSystem needs to be overhauled. Organism.smell will iterate over simulation's food container and 
// generate a scent matrix based on the equation intensity[cell] += sourceStrength * diffusivity / distance from 
// source to cell

using coordPair = std::pair<int, int>;
using coordMap = std::unordered_map<coordPair, qreal, pair_hash>;

class Simulation;

class ScentSystem
{
public:
	friend Simulation;

	ScentSystem(Simulation& pSimulation);

	void init(Simulation& pSimulation);
	void add(coordMap pCoordMap, coordPair pCoords, qreal pAmount);
	void subtract(coordMap pCoordMap, coordPair pCoords, qreal pAmount);
	void update();
	void emanateScent(coordPair pCoords, qreal pScentStrength);
	coordMap scentMap();
	qreal getScent(coordPair pCoords);
	qreal getThreshhold();
	qreal getDiffusivity();
	void reset(Simulation& pSimulation);

private:
	Simulation& mSimulation;
	qreal mThreshhold;
	coordMap mScentMap;
	coordMap mAdditionQueue;
	coordMap mSubtractionQueue;
	qreal mDiffusivity; // needs to be tuned
	qreal mDecayRate;
};

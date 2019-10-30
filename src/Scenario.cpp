#include "Scenario.h"

#include "Simulation.h"
#include "Organism.h"
#include "Creature.h"
#include "Entity.h"

Scenario::Scenario(Simulation* pSimulation)
	: mSimulation(pSimulation) {}

void Scenario::addKeyScore(std::pair<int, qreal> pPair)
{
	mKeyScore.push_back(pPair);
}

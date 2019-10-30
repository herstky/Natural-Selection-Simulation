#include "Scenario/Scenario.h"

#include "Simulation.h"
#include "Model/Entity/Organism/Organism.h"
#include "Model/Entity/Organism/Creature.h"
#include "Model/Entity/Entity.h"

Scenario::Scenario(Simulation* pSimulation)
	: mSimulation(pSimulation) {}

void Scenario::addKeyScore(std::pair<int, qreal> pPair)
{
	mKeyScore.push_back(pPair);
}

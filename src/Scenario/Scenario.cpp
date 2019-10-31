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

void Scenario::simulateTick()
{
	if (mSimulation->mTicksRemaining)
	{
		mSimulation->mTicksRemaining--;
	}
	else
	{
		mSimulation->mTicksRemaining = mSimulation->M_TICKS_PER_STEP;
	}
}

void Scenario::simulateStep()
{
	if (mSimulation->mStepsRemaining)
	{
		mSimulation->mStepsRemaining--;
	}
	else
	{
		endRound();
		mSimulation->start();
	}
}
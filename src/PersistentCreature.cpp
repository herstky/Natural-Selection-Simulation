#include "PersistentCreature.h"

#include <math.h>
#include <QPointF>
#include <QColor>

#include "NeuralNetwork.h"

#include "Simulation.h"
#include "Scenario.h"

qreal PersistentCreature::mCreationChance = 2;
int PersistentCreature::mCount = 0;

PersistentCreature::PersistentCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Creature(pPosition, pBrain, pColor) {}


void PersistentCreature::move(const Simulation& pSimulation)
{
	move(pSimulation);
	mScore -= Organism::mStarvationPenalty * pSimulation.M_TICK_DURATION / 1000.0;
}

void PersistentCreature::eat(Simulation& pSimulation, Entity& pOther)
{
	mScore += mFoodReward;
	pSimulation.scorePoint();

	mEnergyLevel += pOther.getMass() * pOther.getEnergyContent();
	mEnergyLevel = std::min(mEnergyLevel, mEnergyCapacity);
	die(pSimulation);
}

void PersistentCreature::expendEnergy(const Simulation& pSimulation) {}


void PersistentCreature::die(const Simulation& pSimulation)
{
	pSimulation.mScenario->addKeyScore(std::pair<int, qreal>(mKey, mScore));
	Creature::die(pSimulation);
}

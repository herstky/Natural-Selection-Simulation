#include "WeakCreature.h"

#include <math.h>
#include <QPointF>
#include <QColor>

#include "NeuralNetwork.h"

#include "Simulation.h"
#include "Scenario.h"

qreal WeakCreature::mCreationChance = 2;
int WeakCreature::mCount = 0;

WeakCreature::WeakCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Organism(pPosition, pBrain, pColor) 
{
	init();
}

WeakCreature& WeakCreature::operator=(const WeakCreature& pOther)
{
	return *this;
}

WeakCreature::~WeakCreature()
{
	mCount--;
}

void WeakCreature::move(const Simulation& pSimulation)
{
	Organism::move(pSimulation);
	mScore -= Organism::mStarvationPenalty * pSimulation.M_TICK_DURATION / 1000.0;
}

void WeakCreature::eat(Simulation& pSimulation, Entity& pOther)
{
	mScore += mFoodReward;
	pSimulation.scorePoint();

	mEnergyLevel += pOther.getMass() * pOther.getEnergyContent();
	mEnergyLevel = std::min(mEnergyLevel, mEnergyCapacity);
	die(pSimulation);
}

void WeakCreature::expendEnergy(const Simulation& pSimulation) {}


void WeakCreature::die(const Simulation& pSimulation)
{
	pSimulation.mScenario->addKeyScore(std::pair<int, qreal>(mKey, mScore));
	Model::die(pSimulation);
}

const int WeakCreature::count()

{
	return mCount;
}

void WeakCreature::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mReplicationChance = 7;
	mMutationChance = 10;
	mDeathChance = 8;
	mCount++;
}
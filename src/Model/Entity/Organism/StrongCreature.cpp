#include "Model/Entity/Organism/StrongCreature.h"

#include "Simulation.h"

qreal StrongCreature::mCreationChance = 2;
int StrongCreature::mCount = 0;

StrongCreature::StrongCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Organism(pPosition, pBrain, pColor)
{
	init();
}

StrongCreature& StrongCreature::operator=(const StrongCreature& pOther)
{
	return *this;
}

StrongCreature::~StrongCreature()
{
	mCount--;
}

void StrongCreature::move(const Simulation& pSimulation)
{
	Organism::move(pSimulation);
	if (!mHasEaten)
		mScore -= mStarvationPenalty * pSimulation.M_TICK_DURATION / 1000.0;
}

void StrongCreature::eat(Simulation& pSimulation, Entity& pOther)
{
	if (!mHasEaten)
	{
		mHasEaten = true;
		mScore += mFoodReward;
		pSimulation.scorePoint();
	}
}

void StrongCreature::die(const Simulation& pSimulation) {}

void StrongCreature::expendEnergy(const Simulation& pSimulation) {}

const int StrongCreature::count()
{
	return mCount;
}

void StrongCreature::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mReplicationChance = 7;
	mMutationChance = 10;
	mDeathChance = 8;
	mCount++;
}
#include "red.h"

#include "simulation.h"
#include "green.h"

unsigned int Red::mCount = 0;
qreal Red::mCreationChance = 50;

Red::Red(const Simulation& pSimulation)
    : Organism(pSimulation)
{
	init();
}

Red::Red(const Simulation& pSimulation, const QPointF& pPosition)
    : Organism(pSimulation, pPosition)
{
	init();
}


Red::Red(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Organism(pSimulation, pBrain)
{
	init();
}


Red::Red(const Simulation& pSimulation, const QPointF& pPosition, NeuralNetwork pBrain)
	: Organism(pSimulation, pPosition, pBrain)
{
	init();
}

Red::~Red()
{
    mCount--;
}

void Red::replicate(const Simulation& pSimulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Green(pSimulation, QPointF(x(), y()));
    }
    else
    {
        new Red(pSimulation, QPointF(x(), y()));
    }
}

void Red::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mColor = Qt::red;
	mCreationChance = 50;
	mReplicationChance = 7;
	mMutationChance = 10;
	mDeathChance = 8;
	mCount++;
}
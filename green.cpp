#include "green.h"

#include "simulation.h"
#include "blue.h"

unsigned int Green::mCount = 0;
qreal creationChance = 0;

Green::Green(const Simulation& pSimulation)
    : Organism(pSimulation)
{
	init();
}

Green::Green(const Simulation& pSimulation, const QPointF& pPosition)
    : Organism(pSimulation, pPosition)
{
	init();
}

Green& Green::operator=(const Green& pOther)
{
	return *this;
}

Green::~Green()
{
    mCount--;
}

void Green::replicate(const Simulation& pSimulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Blue(pSimulation, QPointF(x(), y()));
    }
    else
    {
        new Green(pSimulation, QPointF(x(), y()));
    }
}

void Green::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mColor = Qt::green;
	mReplicationChance = 8;
	mMutationChance = 5;
	mDeathChance = 8;
	mCount++;
}
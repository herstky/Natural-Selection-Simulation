#include "blue.h"

#include "simulation.h"
#include "green.h"

unsigned int Blue::mCount = 0;
qreal Blue::mCreationChance = 0;

Blue::Blue(const Simulation& pSimulation)
    : Organism(pSimulation)
{
	init();
}

Blue::Blue(const Simulation& pSimulation, const QPointF& pPosition)
	: Organism(pSimulation, pPosition)
{
	init();
}

Blue::~Blue()
{
    mCount--;
}

void Blue::replicate(const Simulation& pSimulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Green(pSimulation, QPointF(x(), y()));
    }
    else
    {
        new Blue(pSimulation, QPointF(x(), y()));
    }
}

void Blue::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mColor = Qt::blue;
	mReplicationChance = 4;
	mMutationChance = 0;
	mDeathChance = 3;
	mCount++;
}

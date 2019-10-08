#include "red.h"

#include "simulation.h"
#include "green.h"

unsigned int Red::mCount = 0;
qreal Red::mCreationChance = 50;

Red::Red(const Simulation& simulation)
    : Organism(simulation)
{
	init();
}

Red::Red(const Simulation& simulation, const QPointF& position)
    : Organism(simulation, position)
{
	init();
}

Red::~Red()
{
    mCount--;
}

void Red::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Green(simulation, QPointF(x(), y()));
    }
    else
    {
        new Red(simulation, QPointF(x(), y()));
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
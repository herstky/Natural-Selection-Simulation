#include "green.h"

#include "simulation.h"
#include "blue.h"

unsigned int Green::mCount = 0;
qreal creationChance = 0;

Green::Green(const Simulation& simulation)
    : Organism(simulation)
{
	mShape = Model::Shape::ellipse;
    mColor = Qt::green;
    mReplicationChance = 8;
    mMutationChance = 5;
    mDeathChance = 8;
    mCount++;
}

Green::Green(const Simulation& simulation, const QPointF& position)
    : Organism(simulation, position)
{
	mShape = Model::Shape::ellipse;
    mColor = Qt::green;
    mReplicationChance = 10;
    mMutationChance = 5;
    mDeathChance = 12;
    mCount++;
}

Green::~Green()
{
    mCount--;
}

void Green::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Blue(simulation, QPointF(x(), y()));
    }
    else
    {
        new Green(simulation, QPointF(x(), y()));
    }
}

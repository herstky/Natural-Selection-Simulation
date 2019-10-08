#include "blue.h"

#include "simulation.h"
#include "green.h"

unsigned int Blue::mCount = 0;
qreal Blue::mCreationChance = 0;

Blue::Blue(const Simulation& simulation)
    : Organism(simulation)
{
	init();
}

Blue::Blue(const Simulation& simulation, const QPointF& position)
	: Organism(simulation, position)
{
	init();
}

Blue::~Blue()
{
    mCount--;
}

void Blue::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mMutationChance)
    {
        new Green(simulation, QPointF(x(), y()));
    }
    else
    {
        new Blue(simulation, QPointF(x(), y()));
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

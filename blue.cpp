#include "blue.h"

#include "simulation.h"
#include "green.h"

unsigned int Blue::count = 0;

Blue::Blue(const Simulation& simulation)
    : Organism(simulation)
{
	shape = ellipse;
    color = Qt::blue;
    creationChance = 0;
    replicationChance = 4;
    mutationChance = 0;
    deathChance = 3;
    count++;
}

Blue::Blue(const Simulation& simulation, const QPointF& position)
    : Organism(simulation, position)
{
	shape = ellipse;
    color = Qt::blue;
    creationChance = 0;
    replicationChance = 10;
    mutationChance = 0;
    deathChance = 5;
    count++;
}

Blue::~Blue()
{
    count--;
}

void Blue::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mutationChance)
    {
        Green* green = new Green(simulation, QPointF(x, y));
    }
    else
    {
        Blue* blue = new Blue(simulation, QPointF(x, y));
    }
}


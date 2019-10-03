#include "green.h"

#include "simulation.h"
#include "blue.h"

unsigned int Green::count = 0;
qreal creationChance = 0;

Green::Green(const Simulation& simulation)
    : Organism(simulation)
{
	shape = Model::Shape::ellipse;
    color = Qt::green;
    replicationChance = 8;
    mutationChance = 5;
    deathChance = 8;
    count++;
}

Green::Green(const Simulation& simulation, const QPointF& position)
    : Organism(simulation, position)
{
	shape = Model::Shape::ellipse;
    color = Qt::green;
    replicationChance = 10;
    mutationChance = 5;
    deathChance = 12;
    count++;
}

Green::~Green()
{
    count--;
}

void Green::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mutationChance)
    {
        new Blue(simulation, QPointF(x(), y()));
    }
    else
    {
        new Green(simulation, QPointF(x(), y()));
    }
}

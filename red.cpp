#include "red.h"

#include "simulation.h"
#include "green.h"

unsigned int Red::count = 0;
qreal Red::creationChance = 50;

Red::Red(const Simulation& simulation)
    : Organism(simulation)
{
	shape = Model::Shape::ellipse;
    color = Qt::red;
    creationChance = 50;
    replicationChance = 7;
    mutationChance = 10;
    deathChance = 8;
    count++;
}

Red::Red(const Simulation& simulation, const QPointF& position)
    : Organism(simulation, position)
{
	shape = Model::Shape::ellipse;
    color = Qt::red;
    creationChance = 50;
    replicationChance = 10;
    mutationChance = 10;
    deathChance = 15;
    count++;
}

Red::~Red()
{
    count--;
}

void Red::replicate(const Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100.0) < mutationChance)
    {
        new Green(simulation, QPointF(x(), y()));
    }
    else
    {
        new Red(simulation, QPointF(x(), y()));
    }
}

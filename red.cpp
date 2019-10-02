#include "red.h"

#include "simulation.h"
#include "green.h"

unsigned int Red::count = 0;

Red::Red(const Simulation& simulation)
    : Organism(simulation)
{
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
        Green* green = new Green(simulation.board.view, position());
    }
    else
    {
        Red* red = new Red(simulation.board.view, position());
    }
}

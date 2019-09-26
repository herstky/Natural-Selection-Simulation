#include "green.h"

#include "simulation.h"
#include "blue.h"

unsigned int Green::count = 0;

Green::Green(QQuickItem* parent)
    : Creature(parent)
{
    color = Qt::green;
    creationChance = 0;
    replicationChance = 8;
    mutationChance = 5;
    deathChance = 8;
    count++;
}

Green::Green(QQuickItem* parent, QPointF position)
    : Creature(parent, position)
{
    color = Qt::green;
    creationChance = 0;
    replicationChance = 10;
    mutationChance = 5;
    deathChance = 12;
    count++;
}

Green::~Green()
{
    count--;
}

void Green::replicate(Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100) < mutationChance)
    {
        Blue* blue = new Blue(simulation.board, position());
    }
    else
    {
        Green* green = new Green(simulation.board, position());
    }
}

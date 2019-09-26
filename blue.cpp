#include "blue.h"

#include "simulation.h"
#include "green.h"

unsigned int Blue::count = 0;

Blue::Blue(QQuickItem* parent)
    : Creature(parent)
{
    color = Qt::blue;
    creationChance = 0;
    replicationChance = 4;
    mutationChance = 0;
    deathChance = 3;
    count++;
}

Blue::Blue(QQuickItem* parent, QPointF position)
    : Creature(parent, position)
{
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

void Blue::replicate(Simulation& simulation)
{
    if (QRandomGenerator::global()->bounded(100) < mutationChance)
    {
        Green* green = new Green(simulation.board, position());
    }
    else
    {
        Blue* blue = new Blue(simulation.board, position());
    }
}


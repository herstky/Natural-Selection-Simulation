#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"

unsigned int Food::count = 0;

Food::Food(const Simulation& simulation)
	: Entity(simulation),
	  creationChance(10),
	  color(Qt::green),
	  energyContent(10),
	  mass(.04),
	  density(1500),
	  aspectRatio(1.5), 
	  depth(1)
{
	count++;
}

Food::Food(const Simulation& simulation, const QPointF& position)
	: Entity(simulation, position),
	creationChance(10),
	color(Qt::green),
	energyContent(10),
	mass(0.1),
	density(1500),
	aspectRatio(1),
	depth(1)
{
	count++;
}

Food::~Food() 
{
	count--;
}

qreal Food::volume()
{
	return mass / density;
}

qreal Food::calculateHeight()
{
	return std::sqrt(volume() / (aspectRatio * depth));
}

qreal Food::calculateWidth()
{
	return aspectRatio * calculateHeight();
}

qreal Food::getCreationChance()
{
	return creationChance;
}

void Food::simulate(const Simulation& simulation) {}

void Food::move(const Simulation& simulation) {}
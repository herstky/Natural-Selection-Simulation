#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"
#include "simulation.h"

unsigned int Food::count = 0;
qreal Food::creationChance = 3;

Food::Food(const Simulation& simulation)
	: Entity(simulation),
	  color(Qt::green),
	  energyContent(10),
	  mass(.005),
	  density(1500),
	  aspectRatio(1.5), 
	  depth(.1)
{
	mX = QRandomGenerator::global()->bounded(simulation.board()->width() - SCALE_FACTOR * width());
	mY = QRandomGenerator::global()->bounded(simulation.board()->height() - SCALE_FACTOR * height());
	initView(simulation);
	count++;
}

Food::Food(const Simulation& simulation, const QPointF& position)
	: Entity(simulation, position),
	color(Qt::green),
	energyContent(10),
	mass(0.005),
	density(1500),
	aspectRatio(1),
	depth(.1)
{
	mX = position.x();
	mY = position.y();
	initView(simulation);
	count++;
}

Food::~Food() 
{
	count--;
}

qreal Food::height()
{
	return std::sqrt(volume() / (aspectRatio * depth));
}

qreal Food::width()
{
	return aspectRatio * height();
}

qreal Food::volume()
{
	return mass / density;
}

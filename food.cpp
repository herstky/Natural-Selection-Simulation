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
	  energyContent(10),
	  mass(.005),
	  density(1500),
	  aspectRatio(1.5), 
	  depth(.1)
{
	color = Qt::green;
	mX = QRandomGenerator::global()->bounded(simulation.board()->width() - scaledWidth());
	mY = QRandomGenerator::global()->bounded(simulation.board()->height() - scaledHeight());
	initView(simulation);
	count++;
}

Food::Food(const Simulation& simulation, const QPointF& position)
	: Entity(simulation, position),
	  energyContent(10),
	  mass(0.005),
	  density(1500),
	  aspectRatio(1),
	  depth(.1)
{
	color = Qt::green;
	mX = position.x();
	mY = position.y();
	initView(simulation);
	count++;
}

Food::~Food() 
{
	count--;
}

void Food::detectCollisions(const Simulation& simulation) {}

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

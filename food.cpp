#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"

unsigned int Food::count = 0;

Food::Food(QQuickItem* parent)
	: Entity(parent),
	  creationChance(10),
	  color(Qt::green),
	  energyContent(10),
	  mass(.04),
	  density(1500),
	  aspectRatio(1.5), 
	  depth(1)
{
	setHeight(SCALE_FACTOR * calculateHeight());
	setWidth(SCALE_FACTOR * calculateWidth());
	qreal x = QRandomGenerator::global()->bounded(parent->width() - width());
	qreal y = QRandomGenerator::global()->bounded(parent->height() - height());
	setPosition(QPointF(x, y));
	setFlag(QQuickItem::ItemHasContents);
	count++;
}

Food::Food(QQuickItem* parent, QPointF position)
	: Entity(parent),
	creationChance(10),
	color(Qt::green),
	energyContent(10),
	mass(0.1),
	density(1500),
	aspectRatio(1),
	depth(1)
{
	setHeight(SCALE_FACTOR * height());
	setWidth(SCALE_FACTOR * width());
	setPosition(position);
	setFlag(QQuickItem::ItemHasContents);
}

Food::~Food() 
{
	count--;
}

void Food::paint(QPainter* painter)
{
	QBrush brush(color);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	painter->drawRoundedRect(contentsBoundingRect(), 2, 2);
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

void Food::simulate(Simulation& simulation) {}

void Food::move(Simulation& simulation) {}
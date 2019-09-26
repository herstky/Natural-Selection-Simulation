#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"

Food::Food(QQuickItem* parent)
	: Entity(parent),
	  creationChance(10),
	  color(Qt::black),
	  energyContent(10),
	  mass(0.1),
	  density(1500),
	  aspectRatio(1), 
	  depth(1)
{
	setHeight(SCALE_FACTOR * height());
	setWidth(SCALE_FACTOR * width());
	qreal x = QRandomGenerator::global()->bounded(parent->width() - width());
	qreal y = QRandomGenerator::global()->bounded(parent->height() - height());
	setPosition(QPointF(x, y));
	setFlag(QQuickItem::ItemHasContents);
}

Food::Food(QQuickItem* parent, QPointF position)
	: Entity(parent),
	creationChance(10),
	color(Qt::black),
	energyContent(10),
	mass(0.1),
	density(1500),
	aspectRatio(1),
	depth(1)
{
	setHeight(SCALE_FACTOR * height());
	setWidth(SCALE_FACTOR * width());
	qreal x = QRandomGenerator::global()->bounded(parent->width() - width());
	qreal y = QRandomGenerator::global()->bounded(parent->height() - height());
	setPosition(QPointF(x, y));
	setFlag(QQuickItem::ItemHasContents);
}

Food::~Food() {}

void Food::paint(QPainter* painter)
{
	QBrush brush(color);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	painter->drawRect(contentsBoundingRect());
}

qreal Food::volume()
{
	return mass / density;
}

qreal Food::height()
{
	return std::sqrt(volume() / (aspectRatio * depth));
}

qreal Food::width()
{
	return aspectRatio * height();
}

qreal Food::getCreationChance()
{
	return creationChance;
}

void Food::simulate(Simulation& simulation) {}

void Food::move(Simulation& simulation) {}
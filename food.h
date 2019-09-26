#pragma once

#include "entity.h"

class Simulation;

class Food : public Entity
{
	Q_OBJECT
public:
	Food(QQuickItem* parent = nullptr);
	Food(QQuickItem* parent, QPointF position);
	~Food();

	void paint(QPainter* painter);

	qreal volume();
	qreal height();
	qreal width();

	qreal getCreationChance();

protected:
	qreal creationChance;
	QColor color;
	qreal energyContent;
	qreal mass;
	qreal density;
	qreal aspectRatio;
	qreal depth;

	void simulate(Simulation& simulation);
	void move(Simulation& simulation);
};


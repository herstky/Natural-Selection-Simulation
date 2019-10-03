#pragma once

#include <QtGlobal>
#include <QColor>

class Simulation;

class Model
{
public:
	enum Status { alive, dead };

	Model();
	Model(const Simulation& simulation);
	Model(const Simulation& simulation, const QPointF& position);
	~Model();

	enum Shape { ellipse, rectangle, roundedRectangle };
	
	Status status;
	QColor color;
	Shape shape;
	qreal height;
	qreal width;
	qreal x;
	qreal y;

};


#pragma once

#include <QtGlobal>
#include <QColor>

class Simulation;

class View;

class Model
{
public:
	enum class Status { alive, dead };
	enum class Shape { ellipse, rectangle, roundedRectangle };

	Model(const Simulation& simulation);
	Model(const Simulation& simulation, const QPointF& position);
	~Model();

	Status status;
	QColor color;
	Shape shape;
	qreal height;
	qreal width;
	qreal x;
	qreal y;
	View* view;

	void initView(const Simulation& simulation);
};


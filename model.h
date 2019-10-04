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
	virtual ~Model();

	Status status;
	QColor color;
	Shape shape;
	View* view;

	virtual qreal height();
	virtual qreal width();
	virtual void setHeight(qreal height);
	virtual void setWidth(qreal width);
	virtual qreal x();
	virtual qreal y();
	virtual void setX(qreal x);
	virtual void setY(qreal y);

	void initView(const Simulation& simulation);

protected:
	qreal mX;
	qreal mY;

private:
	qreal mHeight;
	qreal mWidth;

};


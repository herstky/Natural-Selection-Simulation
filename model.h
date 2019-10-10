#pragma once

#include <QtGlobal>
#include <QColor>
#include <QRectF>

class Simulation;
class View;

class Model
{
	friend class Simulation;

public:
	enum class Status { alive, dead };
	enum class Shape { ellipse, rectangle, roundedRectangle };

	Model(const Simulation& simulation);
	Model(const Simulation& simulation, const QPointF& position);
	virtual ~Model();

	Status mStatus;
	QColor mColor;
	Shape mShape;
	View* mView;

	virtual qreal height();
	virtual qreal width();
	virtual QPointF center();
	virtual QPointF scaledCenter();
	virtual qreal scaledHeight();
	virtual qreal scaledWidth();
	virtual void setHeight(qreal height);
	virtual void setWidth(qreal width);
	virtual qreal x();
	virtual qreal scaledX();
	virtual qreal y();
	virtual qreal scaledY();
	virtual void setX(qreal x);
	virtual void setY(qreal y);
	virtual QRectF hitbox();
	virtual void die(const Simulation& simulation);

	void initView(const Simulation& simulation);

protected:
	qreal mX;
	qreal mY;

	virtual void init();

private:
	qreal mHeight;
	qreal mWidth;
};


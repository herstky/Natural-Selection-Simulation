#pragma once

#include <QtGlobal>
#include <QColor>
#include <QRectF>

#include <utility>

class Simulation;
class View;

class Model
{
	friend class Simulation;

public:
	enum class Status { alive, dead };
	enum class Shape { ellipse, rectangle, roundedRectangle };

	Model(const Simulation& pSimulation);
	Model(const Simulation& pSimulation, const QPointF& pPosition);
	virtual ~Model();

	Status mStatus;
	QColor mColor;
	Shape mShape;
	View* mView;

	virtual const qreal height() const;
	virtual const qreal scaledHeight() const;
	virtual const qreal width() const;
	virtual const qreal scaledWidth() const;
	virtual const QPointF center() const;
	virtual const QPointF scaledCenter() const;
	virtual void setHeight(const qreal pHeight);
	virtual void setWidth(const qreal pWidth);
	virtual const qreal x() const;
	virtual const qreal scaledX() const;
	virtual const qreal y() const;
	virtual const qreal scaledY() const;
	virtual void setX(const qreal pX);
	virtual void setY(const qreal pY);
	const std::pair<int, int>& coords(Simulation& pSimulation) const;
	virtual QRectF hitbox();
	virtual void die(const Simulation& pSimulation);

	void initView(const Simulation& pSimulation);

protected:
	qreal mX;
	qreal mY;

	virtual void init();

private:
	qreal mHeight;
	qreal mWidth;
};


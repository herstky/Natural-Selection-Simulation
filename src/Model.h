#pragma once

#include <QtGlobal>
#include <QColor>
#include <QRectF>

#include <memory>
#include <utility>

#include "constants.h"

// TODO: Consolidate constructors using delegating constructors.

class Simulation;
class View;

class Model : public std::enable_shared_from_this<Model>
{
	friend class Simulation;

public:
	enum class Status { alive, dead };
	enum class Shape { ellipse, rectangle, roundedRectangle };

	Model();
	Model(const QPointF& pPosition);
	virtual ~Model();

	Status mStatus;
	QColor mColor;
	Shape mShape;
	View* mView; // Raw pointer to allow for nullptr and because QT handles memory
	int mKey;

	virtual const qreal height() const;
	virtual const qreal heightP() const;
	virtual const qreal width() const;
	virtual const qreal widthP() const;
	virtual const QPointF center() const;
	virtual const QPointF centerP() const;
	virtual void setHeight(const qreal pHeight);
	virtual void setWidth(const qreal pWidth);
	virtual const qreal x() const;
	virtual const qreal xP() const;
	virtual const qreal y() const;
	virtual const qreal yP() const;
	virtual void setX(const qreal pX);
	virtual void setY(const qreal pY);
	const std::pair<int, int> coords(Simulation& pSimulation) const;
	virtual QRectF hitbox();
	virtual void die(const Simulation& pSimulation);

	void initView(const Simulation& pSimulation);

protected:
	qreal mX;
	qreal mY;

	virtual void init();

private:
	Model(const Model& pOther);
	Model& operator=(const Model& pOther);

	qreal mHeight;
	qreal mWidth;
};


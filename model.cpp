#include "model.h"

#include "simulation.h"
#include "view.h"
#include "constants.h"

Model::Model(const Simulation& simulation)
	: status(Model::Status::alive),
	  color(Qt::black),
	  shape(Model::Shape::rectangle),
	  view(nullptr),
	  mHeight(1),
	  mWidth(1),
      mX(0),
      mY(0) {}

Model::Model(const Simulation& simulation, const QPointF& position) 
	: status(Model::Status::alive),
	  color(Qt::black),
	  shape(Model::Shape::rectangle),
	  view(nullptr),
	  mHeight(1),
	  mWidth(1),
	  mX(position.x()),
	  mY(position.y()) {}

Model::~Model() {}

qreal Model::height()
{
	return mHeight;
}

qreal Model::scaledHeight()
{
	return SCALE_FACTOR * height();
}

void Model::setHeight(qreal height)
{
	mHeight = height;
}

qreal Model::width()
{
	return mWidth;
}

qreal Model::scaledWidth()
{
	return SCALE_FACTOR * width();
}

void Model::setWidth(qreal width)
{
	mWidth = width;
}

qreal Model::x()
{
	return mX;
}

void Model::setX(qreal x)
{
	mX = x;
	view->setX(x);
}

qreal Model::y()
{
	return mY;
}

void Model::setY(qreal y)
{
	mY = y;
	view->setY(y);
}

void Model::initView(const Simulation& simulation)
{
	view = new View(simulation.board(), *this);
	view->init();
}

QRectF Model::hitbox()
{
	return QRectF(x(), y(), scaledWidth(), scaledHeight());
}

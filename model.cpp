#include "model.h"

#include "simulation.h"
#include "view.h"
#include "constants.h"

Model::Model(const Simulation& simulation)
	: mStatus(Model::Status::alive),
	  mColor(Qt::black),
	  mShape(Model::Shape::rectangle),
	  mView(nullptr),
	  mHeight(1),
	  mWidth(1),
      mX(0),
      mY(0) {}

Model::Model(const Simulation& simulation, const QPointF& position) 
	: mStatus(Model::Status::alive),
	  mColor(Qt::black),
	  mShape(Model::Shape::rectangle),
	  mView(nullptr),
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
	mView->setX(x);
}

qreal Model::y()
{
	return mY;
}

void Model::setY(qreal y)
{
	mY = y;
	mView->setY(y);
}

void Model::initView(const Simulation& simulation)
{
	mView = new View(simulation.board(), *this);
	mView->init();
}

QRectF Model::hitbox()
{
	return QRectF(x(), y(), scaledWidth(), scaledHeight());
}

void Model::die(const Simulation& simulation)
{
	mStatus = Model::Status::dead;
	mView->mDeletionQueue.push_back(mView);
}

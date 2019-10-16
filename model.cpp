#include "model.h"

#include "simulation.h"
#include "view.h"
#include "constants.h"

Model::Model(const Simulation& pSimulation)
	: mStatus(Model::Status::alive),
	  mColor(Qt::black),
	  mShape(Model::Shape::rectangle),
	  mView(nullptr),
	  mHeight(1),
	  mWidth(1),
      mX(0),
      mY(0) {}

Model::Model(const Simulation& pSimulation, const QPointF& pPosition) 
	: mStatus(Model::Status::alive),
	  mColor(Qt::black),
	  mShape(Model::Shape::rectangle),
	  mView(nullptr),
	  mHeight(1),
	  mWidth(1),
	  mX(pPosition.x() / SCALE_FACTOR),
	  mY(pPosition.y() / SCALE_FACTOR) {}

Model::~Model() {}

void Model::init() {}

const qreal Model::height() const
{
	return mHeight;
}

const qreal Model::scaledHeight() const
{
	return SCALE_FACTOR * height();
}

void Model::setHeight(const qreal pHeight)
{
	mHeight = pHeight;
}

const qreal Model::width() const
{
	return mWidth;
}

const qreal Model::scaledWidth() const
{
	return SCALE_FACTOR * width();
}

const QPointF Model::center() const
{
	return QPointF(x() + width() / 2.0, y() + height() / 2.0);
}

const QPointF Model::scaledCenter() const
{
	return QPointF(scaledX() + scaledWidth() / 2.0, scaledY() + scaledHeight() / 2.0);
}

void Model::setWidth(const qreal pWidth)
{
	mWidth = pWidth;
}

const qreal Model::x() const
{
	return mX;
}

const qreal Model::scaledX() const
{
	return SCALE_FACTOR * mX;
}

void Model::setX(const qreal pX)
{
	mX = pX;
	mView->setX(SCALE_FACTOR * pX);
}

const qreal Model::y() const
{
	return mY;
}

const qreal Model::scaledY() const
{
	return SCALE_FACTOR * mY;
}

void Model::setY(qreal pY)
{
	mY = pY;
	mView->setY(SCALE_FACTOR * pY);
}

const std::pair<int, int>& Model::coords(Simulation& pSimulation) const
{
	return std::pair<int, int>(int(x() / pSimulation.board()->cellSize()), int(y() / pSimulation.board()->cellSize()));
}

void Model::initView(const Simulation& pSimulation)
{
	mView = new View(pSimulation.boardView(), *this);
	mView->init();
}

QRectF Model::hitbox()
{
	return QRectF(scaledX(), scaledY(), scaledWidth(), scaledHeight());
}

void Model::die(const Simulation& pSimulation)
{
	mStatus = Model::Status::dead;
	mView->mDeletionQueue.push_back(mView);
}

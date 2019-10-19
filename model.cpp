#include "model.h"

#include "simulation.h"
#include "view.h"
#include "constants.h"

Model::Model()
	: mStatus(Model::Status::alive),
	  mColor(Qt::black),
	  mShape(Model::Shape::rectangle),
	  mView(nullptr),
	  mHeight(1),
	  mWidth(1),
	  mX(0),
	  mY(0) {}

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

void Model::init() {}

const qreal Model::height() const
{
	return mHeight;
}

const qreal Model::heightP() const
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

const qreal Model::widthP() const
{
	return SCALE_FACTOR * width();
}

const QPointF Model::center() const
{
	return QPointF(x() + width() / 2.0, y() + height() / 2.0);
}

const QPointF Model::centerP() const
{
	return QPointF(xP() + widthP() / 2.0, yP() + heightP() / 2.0);
}

void Model::setWidth(const qreal pWidth)
{
	mWidth = pWidth;
}

const qreal Model::x() const
{
	return mX;
}

const qreal Model::xP() const
{
	return SCALE_FACTOR * mX;
}

void Model::setX(const qreal pX)
{
	mX = pX;
	mView->setX(xP());
}

const qreal Model::y() const
{
	return mY;
}

const qreal Model::yP() const
{
	return SCALE_FACTOR * mY;
}

void Model::setY(qreal pY)
{
	mY = pY;
	mView->setY(yP());
}

const std::pair<int, int> Model::coords(Simulation& pSimulation) const
{
	return std::pair<int, int>(int(x() / pSimulation.board()->cellSize()), int(y() / pSimulation.board()->cellSize()));
}

void Model::initView(const Simulation& pSimulation)
{
	mView = std::shared_ptr<View>(new View(pSimulation.boardView(), shared_from_this()));
	mView->init();
}

QRectF Model::hitbox()
{
	return QRectF(xP(), yP(), widthP(), heightP());
}

void Model::die(const Simulation& pSimulation)
{
	mStatus = Model::Status::dead;
	View::mDeletionQueue.push_back(mView);
} 

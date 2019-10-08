#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"
#include "simulation.h"

unsigned int Food::mCount = 0;
qreal Food::mCreationChance = 3;

Food::Food(const Simulation& simulation)
	: Entity(simulation)
{
	mX = QRandomGenerator::global()->bounded(simulation.board()->width() - scaledWidth());
	mY = QRandomGenerator::global()->bounded(simulation.board()->height() - scaledHeight());
	init();
	initView(simulation);
}

Food::Food(const Simulation& simulation, const QPointF& position)
	: Entity(simulation, position)
{
	mX = position.x();
	mY = position.y();
	init();
	initView(simulation);
}

Food::~Food() 
{
	mCount--;
}

void Food::detectCollisions(const Simulation& simulation) {}

qreal Food::height()
{
	return std::sqrt(volume() / (mAspectRatio * mDepth));
}

qreal Food::width()
{
	return mAspectRatio * height();
}

qreal Food::volume()
{
	return mMass / mDensity;
}

void Food::init()
{
	mColor = Qt::green;
	mType = Entity::Type::prey;
	mEnergyContent = 128;
	mMass = 0.005;
	mDensity = 1500;
	mAspectRatio = 1;
	mDepth = 0.1;
	mCount++;
}
#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "constants.h"
#include "simulation.h"

unsigned int Food::mCount = 0;
qreal Food::mCreationChance = 10;

Food::Food(const Simulation& simulation)
	: Entity(simulation)
{
	mX = QRandomGenerator::global()->bounded(simulation.boardView()->width() - scaledWidth()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(simulation.boardView()->height() - scaledHeight()) / SCALE_FACTOR;
	init();
	initView(simulation);
}

Food::Food(const Simulation& simulation, const QPointF& position)
	: Entity(simulation, position)
{
	mX = position.x() / SCALE_FACTOR;
	mY = position.y() / SCALE_FACTOR;
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

void Food::emanateScent(Simulation& simulation)
{
	//int i = int(center().x());
	//int j = int(center().y());
	//QPointF c = center();
	//qreal res = simulation.mBoard.mGrid[0][0];
	//simulation.mBoard.mGrid[i][j] = 5.0;
}

void Food::init()
{
	mColor = Qt::green;
	mType = Entity::Type::prey;
	mEnergyContent = 128;
	mMass = 0.005;
	mDensity = 2000;
	mAspectRatio = 1;
	mDepth = 0.1;
	mCount++;
}
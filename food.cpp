#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <cmath>

#include "constants.h"
#include "simulation.h"

unsigned int Food::mCount = 0;
qreal Food::mCreationChance = 5;

Food::Food(Simulation& pSimulation)
	: mScentStrength(1.0), mContainer(pSimulation.mFoodSet)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
	init(pSimulation);
}

Food::Food(Simulation& pSimulation, const QPointF& pPosition)
	: Entity(pPosition), mScentStrength(1.0), mContainer(pSimulation.mFoodSet)
{
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
	init(pSimulation);
}

void Food::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
	mCount--;
}

void Food::detectCollisions(const Simulation& pSimulation) {}

const qreal Food::height() const
{
	return std::sqrt(volume() / (mAspectRatio * mDepth));
}

const qreal Food::width() const
{
	return mAspectRatio * height();
}

const qreal Food::volume() const
{
	return mMass / mDensity;
}

void Food::emanateScent(Simulation& pSimulation)
{
	pSimulation.mScentQueue.emplace(coords(pSimulation), mScentStrength);
}

void Food::simulate(Simulation& pSimulation)
{
	emanateScent(pSimulation);
}

void Food::init(Simulation& pSimulation)
{
	mColor = Qt::green;
	mType = Entity::Type::prey;
	mEnergyContent = 128;
	mMass = 0.005;
	mDensity = 2000;
	mAspectRatio = 1;
	mDepth = 0.1;
	mCount++;
	emanateScent(pSimulation);
}
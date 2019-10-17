#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <cmath>

#include "constants.h"
#include "simulation.h"

unsigned int Food::mCount = 0;
qreal Food::mCreationChance = 10;

Food::Food(const Simulation& pSimulation)
	: Entity(pSimulation), mScentStrength(1.0)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView()->width() - scaledWidth()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView()->height() - scaledHeight()) / SCALE_FACTOR;
	init();
	initView(pSimulation);
}

Food::Food(const Simulation& pSimulation, const QPointF& pPosition)
	: Entity(pSimulation, pPosition), mScentStrength(1.0)
{
	mX = pPosition.x() / SCALE_FACTOR;
	mY = pPosition.y() / SCALE_FACTOR;
	init();
	initView(pSimulation);
}

Food::~Food() 
{
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
	ScentSystem& scentSystem = pSimulation.mScentSystem;
	coordMap& scentMap = scentSystem.scentMap();
	int range = mScentStrength * scentSystem.getDiffusivity() / scentSystem.getThreshhold();
	int offset = -(range / 2);
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			coordPair curCoords = coordPair(coords(pSimulation).first + i + offset, coords(pSimulation).second + j + offset);
			qreal distance = std::sqrt(pow(i + offset, 2) + pow(j + offset, 2));
			qreal intensity = distance ? mScentStrength * scentSystem.getDiffusivity() / distance : mScentStrength;
			qreal curScent = scentMap.count(curCoords) ? scentMap.at(curCoords) : 0;
			curScent = std::max(intensity, curScent);
			if (curScent > scentSystem.getThreshhold())
				scentMap[curCoords] = curScent;
		}
	}
}

void Food::simulate(Simulation& pSimulation)
{
	emanateScent(pSimulation);
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
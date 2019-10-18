#include "food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <cmath>

#include "constants.h"
#include "simulation.h"

unsigned int Food::mCount = 0;
qreal Food::mCreationChance = 50;

Food::Food(Simulation& pSimulation)
	: Entity(pSimulation), mScentStrength(1.0), mContainer(&pSimulation.mFoodSet)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView()->width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView()->height() - heightP()) / SCALE_FACTOR;
	init(pSimulation);
	initView(pSimulation);
}

Food::Food(Simulation& pSimulation, const QPointF& pPosition)
	: Entity(pSimulation, pPosition), mScentStrength(1.0), mContainer(&pSimulation.mFoodSet)
{
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
	init(pSimulation);
	initView(pSimulation);
}

Food::Food(const Food& pOther) : mScentStrength(1.0), mContainer(nullptr) {}

Food& Food::operator=(const Food& pOther)
{
	return *this;
}

Food::~Food() 
{
	mContainer->erase(shared_from_this());
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
	mContainer->emplace(this);
	emanateScent(pSimulation);
}
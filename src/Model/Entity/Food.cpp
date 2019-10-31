#include "Model/Entity/Food.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <cmath>

#include "constants.h"
#include "Simulation.h"

qreal Food::mCreationChance = 5;
int Food::mCount = 0;

Food::Food(Simulation& pSimulation)
	: mContainer(&pSimulation.mFoodSet)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
	init(pSimulation);
}

Food::Food(Simulation& pSimulation, const QPointF& pPosition)
	: Entity(pPosition), mContainer(&pSimulation.mFoodSet)
{
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
	init(pSimulation);
}

Food& Food::operator=(const Food& pOther)
{
	return *this;
}

Food::~Food()
{
	mCount--;
}

void Food::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
}

const qreal Food::creationChance()
{
	return mCreationChance;
}

void Food::setCreationChance(qreal pCreationChance)
{
	mCreationChance = pCreationChance;
}

const int Food::count()
{
	return mCount;
}

void Food::detectCollisions(Simulation& pSimulation) {}

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

void Food::simulate(Simulation& pSimulation) {}

void Food::init(Simulation& pSimulation)
{
	mColor = QColor(124, 252, 0);
	mType = Entity::Type::prey;
	mEnergyContent = 128;
	mMass = 0.008;
	mDensity = 2000;
	mAspectRatio = 1;
	mDepth = 0.1;
	mCount++;
	mPersistent = false;
}

qreal Food::scent(const qreal& distance)
{
	return M_SCENT_DIFFUSIVITY * M_SCENT_STRENGTH / distance;
}
#include "organism.h"

#include <QtMath>
#include <QRandomGenerator>

#include "simulation.h"
#include "constants.h"

#include "view.h"

Organism::Organism(const Simulation& simulation)
    : Entity(simulation),
      mVelocity(3),
      mInitialVelocity(mVelocity),
      mInitialTime(QTime::currentTime()),
      mDeltaDistance(0),
      mDirection(QRandomGenerator::global()->bounded(2 * M_PI)),
      mReplicationChance(0),
      mMutationChance(0),
      mDeathChance(0),
      mMass(0.0005),
      mDensity(WATER_DENSITY),
      mEnergyLevel(100),
      mEnergyCapacity(100)
{
	mX = QRandomGenerator::global()->bounded(simulation.boardView()->width() - scaledWidth());
	mY = QRandomGenerator::global()->bounded(simulation.boardView()->height() - scaledHeight());
	initView(simulation);
}

Organism::Organism(const Simulation& simulation, const QPointF& position)
    : Entity(simulation, position),
      mVelocity(3),
      mInitialVelocity(mVelocity),
      mInitialTime(QTime::currentTime()),
      mDeltaDistance(0),
      mDirection(QRandomGenerator::global()->bounded(2 * M_PI)),
      mReplicationChance(0),
      mMutationChance(0),
      mDeathChance(0),
      mMass(0.0005),
      mDensity(WATER_DENSITY),
      mEnergyLevel(100),
      mEnergyCapacity(100)
{
	mX = position.x() / SCALE_FACTOR;
	mY = position.y() / SCALE_FACTOR;
	initView(simulation);
}

Organism::~Organism() {}

void Organism::move(const Simulation& simulation)
{
	if (mStatus == Model::Status::dead)
	{
		return;
	}

    qreal dx = mVelocity * cos(mDirection);
    qreal dy = mVelocity * sin(mDirection);

    if (x() + dx + width() > simulation.mBoard.width() || x() + dx < 0)
    {
        mDirection = M_PI - mDirection;
    }
    if (y() + dy + height() > simulation.mBoard.height() || y() + dy < 0)
    {
        mDirection = 2 * M_PI - mDirection;
    }

    dx = mVelocity * cos(mDirection);
    dy = mVelocity * sin(mDirection);
    mDeltaDistance = std::sqrt(pow(dx, 2) + pow(dy, 2));

    expendEnergy(simulation);

	//qreal vx = mView->x();
	//qreal vy = mView->y();

	setX(x() + dx);
	setY(y() + dy);
}

void Organism::simulate(Simulation& simulation)
{
	if (mStatus == Model::Status::dead)
	{
		return;
	}
//    if (QRandomGenerator::global()->bounded(100.0) < replicationChance)
//    {
//        replicate(simulation);
//    }
//    if (QRandomGenerator::global()->bounded(100.0) < deathChance)
//    {
//        die(simulation);
//    }
}

void Organism::replicate(const Simulation& simulation)
{
    Organism* organism = new Organism(simulation.boardView(), QPointF(x(), y()));
}

qreal Organism::volume()
{
    return mMass / mDensity;
}

qreal Organism::diameter()
{
   return 2.0 * std::cbrt(3.0 * volume() / (4.0 * M_PI));
}

qreal Organism::deltaVelocity()
{
    return mVelocity - mInitialVelocity;
}

qreal Organism::deltaTime()
{
    return QTime::currentTime().msecsTo(mInitialTime) / 1000.0;
}

qreal Organism::acceleration()
{
    return deltaVelocity() / deltaTime();
}

qreal Organism::x()
{
	return mX;
}

qreal Organism::y()
{
	return mY;
}

qreal Organism::height() 
{
	return diameter();
}

void Organism::setHeight(qreal height) {}

qreal Organism::width()
{
	return diameter();
}

void Organism::setWidth(qreal width) {}

void Organism::expendEnergy(const Simulation& simulation)
{
    qreal drag = 1.0 / 2.0 * SPHERE_WATER_DRAG_COEFFICIENT * WATER_DENSITY * M_PI * pow((diameter() / 2), 2) * pow(mVelocity, 2);

	qreal force = mMass * acceleration() + drag;
    qreal work = force * mDeltaDistance;

	mInitialTime = QTime::currentTime();
	mInitialVelocity = mVelocity;

    mEnergyLevel -= work;
    if (mEnergyLevel <= 0)
    {
        die(simulation);
    }
}

QRectF Organism::hitbox()
{
	qreal radius = SCALE_FACTOR * diameter() / 2.0;
	QPointF center = QPointF(x() + radius, y() + radius);
	QPointF topLeft = QPointF(center.x() + radius * cos(3.0 * M_PI / 4.0), 
						      center.y() - radius * sin(3.0 * M_PI / 4.0));
	QPointF bottomRight = QPointF(center.x() + radius * cos(7.0 * M_PI / 4.0), 
								  center.y() - radius * sin(7.0 * M_PI / 4.0));
	return QRectF(topLeft, bottomRight);
}

void Organism::collide(const Simulation& simulation, Entity& other)
{
	if (other.getType() == Entity::Type::prey)
	{
		eat(simulation, other);
	}
}

void Organism::eat(const Simulation& simulation, Entity& other)
{
	mEnergyLevel += other.getMass() * other.getEnergyContent();
	other.die(simulation);
}

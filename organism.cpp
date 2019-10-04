#include "organism.h"

#include <QtMath>
#include <QRandomGenerator>

#include "simulation.h"
#include "constants.h"

#include "view.h"

Organism::Organism(const Simulation& simulation)
    : Entity(simulation),
      velocity(3),
      prevVelocity(velocity),
      prevTime(QTime::currentTime()),
      dDistance(0),
      direction(QRandomGenerator::global()->bounded(2 * M_PI)),
      replicationChance(0),
      mutationChance(0),
      deathChance(0),
      mass(0.001),
      density(WATER_DENSITY),
      energyLevel(100),
      energyCapacity(100)
{
	mX = QRandomGenerator::global()->bounded(simulation.board()->width() - SCALE_FACTOR * width());
	mY = QRandomGenerator::global()->bounded(simulation.board()->height() - SCALE_FACTOR * height());
	initView(simulation);
}

Organism::Organism(const Simulation& simulation, const QPointF& position)
    : Entity(simulation, position),
      velocity(3),
      prevVelocity(velocity),
      prevTime(QTime::currentTime()),
      dDistance(0),
      direction(QRandomGenerator::global()->bounded(2 * M_PI)),
      replicationChance(0),
      mutationChance(0),
      deathChance(0),
      mass(0.001),
      density(WATER_DENSITY),
      energyLevel(100),
      energyCapacity(100)
{
	mX = position.x();
	mY = position.y();
	initView(simulation);
}

Organism::~Organism() {}

void Organism::move(const Simulation& simulation)
{
    qreal dx = velocity * cos(direction);
    qreal dy = velocity * sin(direction);

    if (x() + dx + SCALE_FACTOR * width() > simulation.board()->width() || x() + dx < 0)
    {
        direction = M_PI - direction;
    }
    if (y() + dy + SCALE_FACTOR * height() > simulation.board()->height() || y() + dy < 0)
    {
        direction = 2 * M_PI - direction;
    }

    dx = velocity * cos(direction);
    dy = velocity * sin(direction);
    dDistance = std::sqrt(pow(dx, 2) + pow(dy, 2));

    expendEnergy(simulation);

	qreal vx = view->x();
	qreal vy = view->y();

	setX(x() + dx);
	setY(y() + dy);
	
	if (status == Model::Status::dead)
	{
		delete this;
	}
}

void Organism::simulate(const Simulation& simulation)
{
//    if (QRandomGenerator::global()->bounded(100.0) < replicationChance)
//    {
//        replicate(simulation);
//    }
//    if (QRandomGenerator::global()->bounded(100.0) < deathChance)
//    {
//        die(simulation);
//    }
	if (status == Model::Status::dead)
	{
		delete this;
		return;
	}
}

void Organism::replicate(const Simulation& simulation)
{
    Organism* organism = new Organism(simulation.board(), QPointF(x(), y()));
}

void Organism::die(const Simulation& simulation)
{
	status = Model::Status::dead;
	view->deleteLater();
}

qreal Organism::volume()
{
    return mass / density;
}

qreal Organism::diameter()
{
   return 2 * std::cbrt(3 * volume() / (4 * M_PI));
}

qreal Organism::dVelocity()
{
    return velocity - prevVelocity;
}

qreal Organism::dTime()
{
    return QTime::currentTime().msecsTo(prevTime) / 1000.0;
}

qreal Organism::acceleration()
{
    return dVelocity() / dTime();
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
    qreal drag = 1.0 / 2.0 * SPHERE_WATER_DRAG_COEFFICIENT * WATER_DENSITY * M_PI * pow((diameter() / 2), 2) * pow(velocity, 2);

	qreal force = mass * acceleration() + drag;
    qreal work = force * dDistance;

	prevTime = QTime::currentTime();
	prevVelocity = velocity;

    energyLevel -= work;
    if (energyLevel <= 0)
    {
        die(simulation);
    }
}

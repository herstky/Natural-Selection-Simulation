#include "creature.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include "simulation.h"
#include "constants.h"

Creature::Creature(QQuickItem* parent)
    : Entity(parent),
      velocity(3),
      prevVelocity(velocity),
      prevTime(QTime::currentTime()),
      dDistance(0),
      direction(QRandomGenerator::global()->bounded(2 * M_PI)),
      color(Qt::black),
      creationChance(0),
      replicationChance(0),
      mutationChance(0),
      deathChance(0),
      mass(.001),
      density(WATER_DENSITY),
      energyLevel(100),
      energyCapacity(100)
{
    setWidth(SCALE_FACTOR * diameter());
    setHeight(SCALE_FACTOR * diameter());
	setZ(1);
    setOpacity(.4);
    qreal x = QRandomGenerator::global()->bounded(parent->width() - width());
    qreal y = QRandomGenerator::global()->bounded(parent->height() - height());
    setPosition(QPointF(x, y));
    setFlag(QQuickItem::ItemHasContents);
}

Creature::Creature(QQuickItem* parent, QPointF position)
    : Entity(parent),
      velocity(3),
      prevVelocity(velocity),
      prevTime(QTime::currentTime()),
      dDistance(0),
      direction(QRandomGenerator::global()->bounded(2 * M_PI)),
      color(Qt::black),
      creationChance(0),
      replicationChance(0),
      mutationChance(0),
      deathChance(0),
      mass(100),
      density(WATER_DENSITY),
      energyLevel(100),
      energyCapacity(100)
{
    setWidth(SCALE_FACTOR * diameter());
    setHeight(SCALE_FACTOR * diameter());
    setOpacity(.4);
    setPosition(position);
    setFlag(QQuickItem::ItemHasContents);
}

Creature::~Creature() {}

void Creature::paint(QPainter* painter)
{
    QBrush brush(color);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->drawEllipse(contentsBoundingRect());
}

void Creature::move(Simulation& simulation)
{
    qreal dx = velocity * cos(direction);
    qreal dy = velocity * sin(direction);

    if (x() + dx + width() > static_cast<QQuickItem*>(parent())->width()
        || x() + dx < 0)
    {
        direction = M_PI - direction;
    }
    if (y() + dy + height() > static_cast<QQuickItem*>(parent())->height()
        || y() + dy < 0)
    {
        direction = 2 * M_PI - direction;
    }

    dx = velocity * cos(direction);
    dy = velocity * sin(direction);
    dDistance = std::sqrt(pow(dx, 2) + pow(dy, 2));

    expendEnergy(simulation);

    setPosition(QPointF(x() + dx, y() + dy));
}

void Creature::simulate(Simulation& simulation)
{
//    if (QRandomGenerator::global()->bounded(100.0) < replicationChance)
//    {
//        replicate(simulation);
//    }
//    if (QRandomGenerator::global()->bounded(100.0) < deathChance)
//    {
//        die(simulation);
//    }
}

void Creature::replicate(Simulation& simulation)
{
    Creature* creature = new Creature(&simulation.board.view);
}

void Creature::die(Simulation& simulation)
{
    deleteLater();
}

qreal Creature::volume()
{
    return mass / density;
}

qreal Creature::diameter()
{
   return 2 * std::cbrt(3 * volume() / (4 * M_PI));
}

qreal Creature::dVelocity()
{
    return velocity - prevVelocity;
}

qreal Creature::dTime()
{
    return QTime::currentTime().msecsTo(prevTime) / 1000.0;
}

qreal Creature::acceleration()
{
    return dVelocity() / dTime();
}

qreal Creature::getCreationChance()
{
	return creationChance;
}

void Creature::expendEnergy(Simulation& simulation)
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

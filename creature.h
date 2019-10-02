#pragma once

#include "entity.h"

#include <QPainter>
#include <QTime>

class Simulation;

class Creature : public Entity 
{
public:
    Creature();
    Creature(QPointF position);
    ~Creature();

    qreal volume();
    qreal diameter();
    qreal dVelocity();
    qreal dTime();
    qreal acceleration();

	qreal getCreationChance();

protected:
	qreal velocity;
	qreal prevVelocity;
	QTime prevTime;
	qreal dDistance;
	qreal direction;
	QColor color;
	qreal creationChance;
	qreal replicationChance;
	qreal mutationChance;
	qreal deathChance;

	qreal mass;
	qreal density;
	qreal energyLevel;
	qreal energyCapacity;

    void expendEnergy(Simulation& simulation);
	void move(Simulation& simulation);
	void simulate(Simulation& simulation);
	virtual void replicate(Simulation& simulation);
	virtual void die(Simulation& simulation);
};


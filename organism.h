#pragma once

#include "entity.h"

#include <QPainter>
#include <QTime>

class Simulation;

class Organism : public Entity 
{
public:
    Organism(const Simulation& simulation);
    Organism(const Simulation& simulation, const QPointF& position);
    ~Organism();

    qreal volume();
    qreal diameter();
    qreal dVelocity();
    qreal dTime();
    qreal acceleration();

protected:
	qreal velocity;
	qreal prevVelocity;
	QTime prevTime;
	qreal dDistance;
	qreal direction;
	qreal replicationChance;
	qreal mutationChance;
	qreal deathChance;

	qreal mass;
	qreal density;
	qreal energyLevel;
	qreal energyCapacity;

    void expendEnergy(const Simulation& simulation);
	void move(const Simulation& simulation) override;
	void simulate(const Simulation& simulation) override;
	virtual void replicate(const Simulation& simulation);
	virtual void die(const Simulation& simulation);
};


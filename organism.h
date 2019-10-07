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
    virtual ~Organism() override;

    qreal volume();
    qreal diameter();
    qreal dVelocity();
    qreal dTime();
    qreal acceleration();

	void move(const Simulation& simulation) override;
	void simulate(const Simulation& simulation) override;

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

	qreal x() override;
	qreal y() override;
	qreal height() override;
	void setHeight(qreal height) override;
	qreal width() override;
	void setWidth(qreal width) override;
    void expendEnergy(const Simulation& simulation);
	virtual void replicate(const Simulation& simulation);
};


#pragma once

#include "entity.h"

#include <QPainter>
#include <QTime>

class Simulation;

class Organism : public Entity 
{
	friend class Simulation;
public:
    Organism(const Simulation& pSimulation);
    Organism(const Simulation& pSimulation, const QPointF& pPosition);
    virtual ~Organism() override;

    const qreal volume() const;
    const qreal diameter() const;
    qreal deltaVelocity();
    qreal deltaTime();
    qreal acceleration();

	void move(const Simulation& pSimulation) override;
	void simulate(Simulation& pSimulation) override;

	void eat(const Simulation& pSimulation, Entity& pOther);

protected:
	qreal mVelocity; // [m/s]
	qreal mInitialVelocity; // [m/s]
	QTime mInitialTime; 
	qreal mDeltaDistance; // [m]
	qreal mDirection; // [rad]
	qreal mReplicationChance;
	qreal mMutationChance;
	qreal mDeathChance;

	qreal mMass; // [kg]
	qreal mDensity; // [kg/m^3]
	qreal mEnergyLevel;
	qreal mEnergyCapacity;

	const qreal height() const override;
	void setHeight(qreal pHeight) override;
	const qreal width() const override;
	void setWidth(qreal pWidth) override;
    void expendEnergy(const Simulation& pSimulation);
	virtual void replicate(const Simulation& pSimulation);
	virtual QRectF hitbox() override;
	virtual void collide(const Simulation& pSimulation, Entity& pOther) override;
};


#pragma once

#include "entity.h"

#include <QPainter>
#include <QTime>
#include <armadillo>

#include "neuralnetwork.h"

class Simulation;

class Organism : public Entity 
{
	friend class Simulation;
public:
	Organism();
    Organism(const QPointF& pPosition);
	Organism(const Simulation& pSimulation, NeuralNetwork pBrain);
	Organism(const Simulation& pSimulation, const QPointF& pPosition, NeuralNetwork pBrain);

    const qreal volume() const;
    const qreal diameter() const;
    qreal deltaVelocity();
    qreal deltaTime();
    qreal acceleration();

	void move(const Simulation& pSimulation) override;
	void simulate(Simulation& pSimulation) override;

	arma::mat smell(Simulation& pSimulation);
	void think(Simulation& pSimulation);
	void eat(const Simulation& pSimulation, Entity& pOther);

protected:
	NeuralNetwork mBrain;
	qreal mMaxSpeed; // [m/s]
	qreal mVelocity; // [m/s]
	qreal mInitialVelocity; // [m/s]
	QTime mInitialTime; 
	qreal mDeltaDistance; // [m]
	qreal mDirection; // [rad]
	qreal mReplicationChance;
	qreal mMutationChance;
	qreal mDeathChance;
	qreal mScentStrength;

	qreal mMass; // [kg]
	qreal mDensity; // [kg/m^3]
	qreal mEnergyLevel;
	qreal mEnergyCapacity;
	qreal mEnergySpent;
	qreal mScore;

	virtual void init(Simulation& pSimulation);

	const qreal height() const override;
	void setHeight(qreal pHeight) override;
	const qreal width() const override;
	void setWidth(qreal pWidth) override;
    void expendEnergy(const Simulation& pSimulation);
	virtual void replicate(const Simulation& pSimulation);
	virtual QRectF hitbox() override;
	virtual void collide(Simulation& pSimulation, Entity& pOther) override;
};


#pragma once

#include "Model/Entity/Entity.h"

#include <string>

#include <QPainter>
#include <QTime>

#include <armadillo>

#include "NeuralNetwork.h"

class Simulation;

class Organism : public Entity 
{
	friend class Simulation;
	friend class CircleTrainingScenario;
public:
	Organism();
    Organism(const QPointF& pPosition);
	Organism(const Simulation& pSimulation, NeuralNetwork pBrain);
	Organism(const QPointF& pPosition, NeuralNetwork pBrain);
	Organism(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);
	virtual ~Organism() override;

    const qreal volume() const;
    const qreal diameter() const;
    qreal deltaVelocity();
    qreal deltaTime();
    qreal acceleration();
	qreal& score();
	qreal& energyLevel();
	qreal energyCapacity();
	qreal foodReward();

	virtual void die(const Simulation& pSimulation) override;
	virtual void move(const Simulation& pSimulation) override;
	virtual void simulate(Simulation& pSimulation) override;

	arma::mat smell(Simulation& pSimulation);
	virtual void think(Simulation& pSimulation);
	virtual void eat(Simulation& pSimulation, Entity& pOther);
	virtual void expendEnergy(const Simulation& pSimulation);

	static NeuralNetwork loadBrain();
	static NeuralNetwork loadBrain(std::string pPath);

	bool mHasEaten;

	static qreal mStarvationPenalty;
	static qreal mOutOfBoundsPenalty;
	static qreal mNoScentsPenalty;
	static qreal mEnergyExpenditurePenalty;
	static qreal mFoodReward;
	static qreal mScentReward;
	static qreal mScentIncreaseReward;
	static qreal mScentDecreasePenalty;

protected:
	NeuralNetwork mBrain;
	qreal mMass; // [kg]
	qreal mDensity; // [kg/m^3]
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
	qreal mSmellRadius; // [m]
	qreal mScentThreshhold;
	qreal mEnergyLevel;
	qreal mEnergyCapacity;
	qreal mEnergySpent;
	qreal mScore;
	qreal mPrevScentSum;

	virtual void init(Simulation& pSimulation);

	const qreal height() const override;
	void setHeight(qreal pHeight) override;
	const qreal width() const override;
	void setWidth(qreal pWidth) override;
	virtual void replicate(const Simulation& pSimulation);
	virtual QRectF hitbox() override;
	virtual void collide(Simulation& pSimulation, Entity& pOther) override;

private:
	Organism(const Organism& pOther);
	Organism& operator=(const Organism& pOther);
};


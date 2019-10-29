#pragma once

#include "Creature.h"

#include <QPointF>
#include "NeuralNetwork.h"

class Simulation;
class Entity;

class PersistentCreature : public Creature
{
public:
	PersistentCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);

	virtual void move(const Simulation& pSimulation) override;
	virtual void eat(Simulation& pSimulation, Entity& pOther) override;
	virtual void expendEnergy(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

	inline static const int count()
	{
		return mCount;
	}

private:
	static qreal mCreationChance;
	static int mCount;
};


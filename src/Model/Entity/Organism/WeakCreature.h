#pragma once

#include "Model/Entity/Organism/Organism.h"

#include <QPointF>
#include "NeuralNetwork.h"

class Simulation;
class Entity;

// This variant of the Creature class is meant for training. WeakCreature does not expend any 
// energy and will die once it reaches food, without destroying the food object.
class WeakCreature : public Organism
{
public:
	WeakCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);
	virtual ~WeakCreature() override;

	virtual void move(const Simulation& pSimulation) override;
	virtual void eat(Simulation& pSimulation, Entity& pOther) override;
	virtual void expendEnergy(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

	static const int count();

protected:
	virtual void init() override;

private:
	WeakCreature(const WeakCreature& pOther) {}
	WeakCreature& operator=(const WeakCreature& pOther);

	static qreal mCreationChance;
	static int mCount;
};


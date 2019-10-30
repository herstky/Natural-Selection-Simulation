#pragma once

#include "Organism.h"

#include <QPointF>
#include "NeuralNetwork.h"

class Simulation;
class Entity;

class WeakCreature : public Organism
{
public:
	WeakCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);

	virtual void move(const Simulation& pSimulation) override;
	virtual void eat(Simulation& pSimulation, Entity& pOther) override;
	virtual void expendEnergy(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;
	virtual ~WeakCreature() override;

	static const int count();

protected:
	virtual void init() override;

private:
	WeakCreature(const WeakCreature& pOther) {}
	WeakCreature& operator=(const WeakCreature& pOther);
	static qreal mCreationChance;
	static int mCount;
};


#pragma once

#include "Model/Entity/Organism/Organism.h"

class Simulation;

class StrongCreature : public Organism
{
public:
	StrongCreature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);
	virtual ~StrongCreature() override;

	virtual void move(const Simulation& pSimulation) override;
	virtual void eat(Simulation& pSimulation, Entity& pOther) override;
	virtual void die(const Simulation& pSimulation) override;
	virtual void expendEnergy(const Simulation& pSimulation) override;
	static const int count();

protected:
	virtual void init() override;

private:
	StrongCreature(const StrongCreature& pOther) {}
	StrongCreature& operator=(const StrongCreature& pOther);
	static qreal mCreationChance;
	static int mCount;


};


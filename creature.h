#pragma once

#include "organism.h"

class Creature : public Organism
{
	friend class Simulation;

public:
    Creature();
	Creature(const Simulation& pSimulation);
    Creature(const QPointF& pPosition);
	Creature(const Simulation& pSimulation, NeuralNetwork pBrain);
	Creature(const QPointF& pPosition, NeuralNetwork pBrain);
	Creature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);
    ~Creature();

    void replicate(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	Creature(const Creature& pOther) {}
	Creature& operator=(const Creature& pOther);

	static unsigned int mCount;
	static qreal mCreationChance;
};


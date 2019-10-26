#pragma once

#include "Organism.h"

class Simulation;

class Creature : public Organism
{
	friend class Simulation;
	friend class SimTrainingScenario;
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

	static unsigned int mCount;

protected:
	virtual void init() override;

private:
	Creature(const Creature& pOther) {}
	Creature& operator=(const Creature& pOther);

	static qreal mCreationChance;
};


#pragma once

#include "organism.h"

class Red : public Organism
{
	friend class Simulation;

public:
    Red();
	Red(const Simulation& pSimulation);
    Red(const QPointF& pPosition);
	Red(const Simulation& pSimulation, NeuralNetwork pBrain);
	Red(const QPointF& pPosition, NeuralNetwork pBrain);
    ~Red();

    void replicate(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	Red(const Red& pOther) {}
	Red& operator=(const Red& pOther);

	static unsigned int mCount;
	static qreal mCreationChance;
};


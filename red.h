// TODO: Need to store training scores in a replicate group

#pragma once

#include "organism.h"

class Red : public Organism
{
	friend class Simulation;

public:
    Red(const Simulation& pSimulation);
    Red(const Simulation& pSimulation, const QPointF& pPosition);
	Red(const Simulation& pSimulation, NeuralNetwork pBrain);
	Red(const Simulation& pSimulation, const QPointF& pPosition, NeuralNetwork pBrain);
    ~Red();

    void replicate(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	Red(const Red& pOther) {}
	Red& operator=(const Red& pOther);

	static unsigned int mCount;
	static qreal mCreationChance;
};


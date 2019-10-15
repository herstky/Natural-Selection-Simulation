#pragma once

#include "organism.h"

class Red : public Organism
{
	friend class Simulation;

public:
    Red(const Simulation& pSimulation);
    Red(const Simulation& pSimulation, const QPointF& pPosition);
    ~Red() override;

    void replicate(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;
};


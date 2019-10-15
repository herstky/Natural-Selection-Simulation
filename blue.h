#pragma once

#include "organism.h"

class Blue : public Organism
{
	friend class Simulation;

public:
    Blue(const Simulation& pSimulation);
    Blue(const Simulation& pSimulation, const QPointF& pPosition);
    ~Blue() override;
    
    void replicate(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;
};

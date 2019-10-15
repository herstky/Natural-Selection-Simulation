#pragma once

#include "organism.h"

class Green : public Organism
{
	friend class Simulation;

public:
    Green(const Simulation& pSimulation);
    Green(const Simulation& pSimulation, const QPointF& pPosition);
    ~Green() override;

    void replicate(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;
};


#pragma once

#include "organism.h"

class Blue : public Organism
{
	friend class Simulation;

public:
    Blue();
    Blue(const QPointF& pPosition);
    ~Blue();
    
    void replicate(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	Blue(const Blue& pOther) {}
	Blue& operator=(const Blue& pOther);

	static unsigned int mCount;
	static qreal mCreationChance;
};

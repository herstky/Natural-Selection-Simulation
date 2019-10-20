#pragma once

#include "organism.h"

class Green : public Organism
{
	friend class Simulation;

public:
    Green();
    Green(const QPointF& pPosition);
    ~Green();

    void replicate(const Simulation& pSimulation) override;

protected:
	virtual void init() override;

private:
	Green(const Green& pOther) {}
	Green& operator=(const Green& pOther);

	static unsigned int mCount;
	static qreal mCreationChance;
};


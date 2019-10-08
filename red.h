#pragma once

#include "organism.h"

class Red : public Organism
{
	friend class Simulation;

public:
    Red(const Simulation& simulation);
    Red(const Simulation& simulation, const QPointF& position);
    ~Red() override;

    void replicate(const Simulation& simulation) override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;

	virtual void init() override;
};


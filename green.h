#pragma once

#include "organism.h"

class Green : public Organism
{
	friend class Simulation;
public:
    Green(const Simulation& simulation);
    Green(const Simulation& simulation, const QPointF& position);
    ~Green() override;

    void replicate(const Simulation& simulation) override;

private:
	static unsigned int count;
	static qreal creationChance;
};


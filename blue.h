#pragma once

#include "organism.h"

class Blue : public Organism
{
public:
    Blue(const Simulation& simulation);
    Blue(const Simulation& simulation, const QPointF& position);
    ~Blue();
    
	static unsigned int count;
	static qreal creationChance;

    void replicate(const Simulation& simulation) override;
};

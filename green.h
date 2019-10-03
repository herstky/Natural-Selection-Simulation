#pragma once

#include "organism.h"

class Green : public Organism
{
public:
    Green(const Simulation& simulation);
    Green(const Simulation& simulation, const QPointF& position);
    ~Green();
    static unsigned int count;
    void replicate(const Simulation& simulation) override;
};


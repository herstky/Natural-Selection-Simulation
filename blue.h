#pragma once

#include "organism.h"

class Blue : public Organism
{
public:
    Blue(const Simulation& simulation);
    Blue(const Simulation& simulation, const QPointF& position);
    ~Blue() override;
    static unsigned int count;
    void replicate(Simulation& simulation) override;
};

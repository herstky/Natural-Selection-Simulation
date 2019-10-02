#pragma once

#include "organism.h"

class Red : public Organism
{
public:
    Red(const Simulation& simulation);
    Red(const Simulation& simulation, const QPointF& position);
    ~Red() override;
    static unsigned int count;
    void replicate(const Simulation& simulation) override;
};


#pragma once

#include "creature.h"

class Blue : public Creature
{
public:
    Blue(QQuickItem* parent = nullptr);
    Blue(QQuickItem* parent, QPointF position);
    ~Blue() override;
    static unsigned int count;
    void replicate(Simulation& simulation) override;
};

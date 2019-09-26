#pragma once

#include "creature.h"

class Red : public Creature
{
public:
    Red(QQuickItem* parent = nullptr);
    Red(QQuickItem* parent, QPointF position);
    ~Red() override;
    static int count;
    void replicate(Simulation& simulation) override;
};


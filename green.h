#pragma once

#include "creature.h"

class Green : public Creature
{
public:
    Green(QQuickItem* parent = nullptr);
    Green(QQuickItem* parent, QPointF position);
    ~Green() override;
    static int count;
    void replicate(Simulation& simulation) override;
};


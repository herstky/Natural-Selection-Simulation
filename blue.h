#ifndef BLUE_H
#define BLUE_H

#include "creature.h"

class Blue : public Creature
{
public:
    Blue(QQuickItem* parent = nullptr);
    Blue(QQuickItem* parent, QPointF position);
    ~Blue() override;
    static int count;
    void replicate(Simulation& simulation) override;
};

#endif // BLUE_H

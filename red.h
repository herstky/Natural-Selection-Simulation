#ifndef RED_H
#define RED_H

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

#endif // RED_H

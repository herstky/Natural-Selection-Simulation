#ifndef CREATURE_H
#define CREATURE_H

#include <QQuickPaintedItem>
#include <QRandomGenerator>

#include <QPainter>
#include <QTime>

class Simulation;

class Creature : public QQuickPaintedItem {
    Q_OBJECT
public:
    Creature(QQuickItem* parent = nullptr);
    Creature(QQuickItem* parent, QPointF position);
    ~Creature();
    void paint(QPainter* painter);
    qreal velocity;
    qreal prevVelocity;
    QTime prevTime;
    qreal dDistance;
    qreal direction;
    QColor color;
    qreal creationChance;
    qreal replicationChance;
    qreal mutationChance;
    qreal deathChance;

    qreal mass;
    qreal density;
    qreal energyLevel;
    qreal energyCapacity;

    virtual void replicate(Simulation& simulation);
    virtual void die(Simulation& simulation);
    void move(Simulation& simulation);
    void simulate(Simulation& simulation);

    qreal volume();
    qreal diameter();
    qreal dVelocity();
    qreal dTime();
    qreal acceleration();
    void expendEnergy(Simulation& simulation);
};

#endif // CREATURE_H

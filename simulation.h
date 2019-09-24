#ifndef SIMULATION_H
#define SIMULATION_H

#include <QQuickItem>
#include <QTimer>
#include <QObject>
#include <QRandomGenerator>

#include <vector>

#include "creature.h"

class Simulation : QObject
{
    Q_OBJECT
public:
    Simulation(QQuickItem* board = 0);
    ~Simulation();
    QQuickItem* board;
    std::vector<Creature*> creatures;

public slots:
    void run();
private:
    void outputCounts(QQuickItem* board);
    const int TICK_DURATION;
    const int TICKS_PER_STEP;
    int ticksRemaining;
};

#endif // SIMULATION_H

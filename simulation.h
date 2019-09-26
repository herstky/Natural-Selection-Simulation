#pragma once

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

public slots:
    void run();
private:
    void outputCounts(QQuickItem* board);
    const int TICK_DURATION;
    const int TICKS_PER_STEP;
    int ticksRemaining;
};

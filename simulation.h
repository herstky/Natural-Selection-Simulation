#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QObject>
#include <QRandomGenerator>

#include <vector>

#include "creature.h"
#include "board.h"

class Simulation : QObject
{
    Q_OBJECT
public:
    Simulation(QQuickItem* parent = nullptr);
    ~Simulation();
	QQuickItem* container;
    Board* board;

public slots:
    void run();

private:
    void outputCounts();
    const int TICK_DURATION;
    const int TICKS_PER_STEP;
    int ticksRemaining;
};

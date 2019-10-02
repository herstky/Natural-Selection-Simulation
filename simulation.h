#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QObject>
#include <QRandomGenerator>

#include <vector>

#include "organism.h"
#include "board.h"

class Simulation : QObject
{
    Q_OBJECT
public:
    Simulation(QQuickItem* parent);
    ~Simulation();
	QQuickItem& container;

	QQuickItem* board() const;

public slots:
    void run();

private:
    const int TICK_DURATION;
    const int TICKS_PER_STEP;
    int ticksRemaining;

	void outputCounts();
};

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
	QQuickItem& mContainer;

	QQuickItem* board() const;

public slots:
    void run();

private:
    const int M_TICK_DURATION;
    const int M_TICKS_PER_STEP;
    int mTicksRemaining;

	void outputCounts();
};

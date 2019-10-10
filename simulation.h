#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QRandomGenerator>

#include <vector>

#include "organism.h"
#include "board.h"

class Simulation : QObject
{
	Q_OBJECT
public:
	friend class Entity;
	friend class Food;
	friend class Organism;
    Simulation(QQuickItem* parent);
    ~Simulation();
	QQuickItem& mContainer;

	QQuickItem* boardView() const;
	qreal deltaTime() const;

public slots:
    void run();

protected:
	void init();

private:
	Board mBoard;
    const int M_TICK_DURATION; // [ms]
    const int M_TICKS_PER_STEP; // simulate only called every step
    int mTicksRemaining;
	QTime mInitialTime; // time since previous step

	void outputCounts();
};

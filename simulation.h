#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QRandomGenerator>
#include <QFuture>

#include <vector>

#include "organism.h"
#include "board.h"
#include "scentsystem.h"

class Simulation : QObject
{
	Q_OBJECT
public:
	friend class Entity;
	friend class Food;
	friend class Organism;
    Simulation(QQuickItem* pParent);
    ~Simulation();
	QQuickItem& mContainer;

	QQuickItem* boardView() const;
	qreal deltaTime() const;
	Board* board();

public slots:
    void run();

protected:
	void init();

private:
	Board mBoard;
	ScentSystem mScentSystem;
	QFuture<void> mDiffusionThread;
    const int M_TICK_DURATION; // [ms]
    const int M_TICKS_PER_STEP; // simulate only called every step
    int mTicksRemaining;
	QTime mInitialTime; // time since previous step
	
	void outputCounts();
};

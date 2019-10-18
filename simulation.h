#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QRandomGenerator>
#include <QFuture>

#include <vector>
#include <unordered_set>

#include "organism.h"
#include "board.h"
#include "scentsystem.h"

class Simulation : QObject
{
	Q_OBJECT
public:
	enum class Mode { simulate, train };

	friend class Entity;
	friend class Food;
	friend class Organism;
    
	Simulation(QQuickItem* pParent);
    Simulation(QQuickItem* pParent, Mode pMode);
    ~Simulation();
	
	QQuickItem& mContainer;

	void addOrganism(Organism* pOrganism);
	void addOrganismGroup(std::vector<Organism*>* pGroup);
	QQuickItem* boardView() const;
	qreal deltaTime() const;
	Board* board();
	void simulate();
	void train();
	

public slots:
    void run();

protected:
	void init();

private:
	Mode mMode;
	Board mBoard;
	ScentSystem mScentSystem;
	QFuture<void> mDiffusionThread;
    const int M_TICK_DURATION; // [ms]
    const int M_TICKS_PER_STEP; // simulate only called every step
    int mTicksRemaining;
	QTime mInitialTime; // time since previous step
	std::unordered_set<Food*> mFoodSet;
	std::vector<std::vector<Organism*>*> mOrganismGroups;

	void outputCounts();
};

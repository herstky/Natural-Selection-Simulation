#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QRandomGenerator>
#include <QFuture>

#include <vector>
#include <unordered_set>
#include <memory>

#include "utils.h"
#include "organism.h"
#include "board.h"

// TODO: Need to be able to turn off animation and run sim as fast as possible.

using coordPair = std::pair<int, int>;

class Simulation : public QObject
{
	Q_OBJECT
public:
	enum class Mode { debug, train, simulate };

	friend class Entity;
	friend class Food;
	friend class Organism;
    
	Simulation(QQuickItem* pParent);
    Simulation(QQuickItem* pParent, Mode pMode);
	
	QQuickItem& mContainer;

	void addOrganism(std::shared_ptr<Organism> pOrganism);
	void addOrganismGroup(std::vector<std::shared_ptr<Organism>> pGroup);
	void addFood(std::shared_ptr<Food> pFood);
	void removeFood(std::shared_ptr<Food> pFood);
	QQuickItem& boardView() const;
	qreal deltaTime() const;
	Board& board();
	void simulate();
	void train();

public slots:
    void run();

private:
	Mode mMode;
	Board mBoard;
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	QTimer* mTimer;
    const int M_TICK_DURATION; // [ms]
    const int M_TICKS_PER_STEP; // simulate only called every step
	const int M_STEPS_PER_ROUND;
    int mTicksRemaining;
	int mStepsRemaining;
	int mGeneration;
	qreal mScore;
	QTime mInitialTime; // time since previous step
	bool mAnimate;
	std::unordered_set<std::shared_ptr<Food>> mFoodSet;
	std::vector<std::vector<std::shared_ptr<Organism>>> mOrganismGroups;
	std::vector<std::shared_ptr<Entity>> mInitViewQueue;

	void start(const NeuralNetwork& pNeuralNetwork);
	void init(const NeuralNetwork& pNeuralNetwork);
	void outputCounts();
};

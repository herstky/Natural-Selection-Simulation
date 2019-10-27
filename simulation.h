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
#include "Organism.h"
#include "Board.h"
#include "NeuralNetwork.h"

// TODO: Need to be able to turn off animation and run sim as fast as possible.

using coordPair = std::pair<int, int>;
using nnScorePair = std::pair<NeuralNetwork, qreal>;

class Simulation : public QObject
{
	Q_OBJECT
public:
	enum class Mode { debug, train, simulate };

	friend class Entity;
	friend class Food;
	friend class Organism;

	Simulation(QQuickItem* pParent, Mode pMode = Mode::simulate);

	Mode mMode;
	QQuickItem& mContainer;
	const int M_TICK_DURATION; // [ms]
	const int M_TICKS_PER_STEP; // simulate only called every step
	const int M_STEPS_PER_ROUND;

	int mTicksRemaining;
	int mStepsRemaining;
	QTime mInitialTime; // time since previous step

	void addOrganism(std::shared_ptr<Organism> pOrganism);
	void addOrganismGroup(std::vector<std::shared_ptr<Organism>> pGroup);
	void addFood(std::shared_ptr<Food> pFood);
	void removeFood(std::shared_ptr<Food> pFood);
	QQuickItem& boardView() const;
	qreal deltaTime() const;
	Board& board();
	void simulate();
	void train();

	void start();
	QTimer* timer();
	const int ticksRemaining();
	const int stepsRemaining();
	const int generation();
	const int score();
	void scorePoint();
	std::vector<std::vector<std::shared_ptr<Organism>>>& organismGroups();

public slots:
	void run();

private:
	Board mBoard;
	std::shared_ptr<Scenario> mScenario;
	QTimer* mTimer;
	int mGeneration;
	qreal mScore;
	QObject* mAnimateCheckBox;
	bool mAnimated;
	std::unordered_set<std::shared_ptr<Food>> mFoodSet;
	std::vector<std::vector<std::shared_ptr<Organism>>> mOrganismGroups;
	std::vector<std::shared_ptr<Entity>> mInitViewQueue;

	void init();
};

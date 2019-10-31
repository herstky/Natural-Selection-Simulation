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
#include "Model/Entity/Organism/Organism.h"
#include "Board.h"
#include "NeuralNetwork.h"
#include "Scenario/Training/CircleTraining/CircleTraining.h"
#include "Scenario/Training/CircleTraining/QuickWeak.h"
#include "Scenario/Training/CircleTraining/NoCrossOver.h"
#include "Scenario/SimScenario.h"

class Simulation : public QObject
{
	Q_OBJECT
public:
	using coordPair = std::pair<int, int>;
	using nnScorePair = std::pair<NeuralNetwork, qreal>;
	using ScenarioType = SimScenario;

	enum class Mode { debug, train, simulate };

	friend class Entity;
	friend class Food;
	friend class Organism;
	friend class QuickWeak;

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
	std::shared_ptr<Scenario> mScenario;

public slots:
	void run();

private:
	Board mBoard;
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

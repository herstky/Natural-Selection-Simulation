#include "Simulation.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>
#include <QRandomGenerator>

#include <iostream>
#include <algorithm>
#include <string>
#include <limits>

#include "constants.h"
#include "Scenario.h"
#include "SimScenario.h"
#include "DebugScenario.h"
#include "View.h"
#include "Model.h"
#include "Entity.h"
#include "Creature.h"
#include "Food.h"
#include "NeuralNetwork.h"
#include "Organism.h"

Simulation::Simulation(QQuickItem* pParent, Mode pMode)
	: mMode(pMode),
	  mContainer(*pParent),
	  mBoard(Board(*mContainer.findChild<QQuickItem*>("board"))),
	  mScenario(std::make_shared<ScenarioType>(ScenarioType(this,
		  nnScorePair(Organism::loadBrain("data//saved//102919/G60k"),
		  -std::numeric_limits<qreal>::infinity())))),
	  M_TICK_DURATION(50),
	  M_TICKS_PER_STEP(5),
	  M_STEPS_PER_ROUND(50),
	  mTicksRemaining(M_TICKS_PER_STEP),
	  mStepsRemaining(M_STEPS_PER_ROUND),
	  mGeneration(0),
	  mScore(0),
	  mInitialTime(QTime::currentTime()),
	  mAnimateCheckBox(mContainer.findChild<QObject*>("animateCheckBox")),
      mAnimated(true),
	  mFoodSet(std::unordered_set<std::shared_ptr<Food>>()),
	  mOrganismGroups(std::vector<std::vector<std::shared_ptr<Organism>>>()),
	  mInitViewQueue(std::vector<std::shared_ptr<Entity>>())
{
	init();
}

void Simulation::addOrganism(std::shared_ptr<Organism> pOrganism)
{
	mOrganismGroups.push_back(std::vector<std::shared_ptr<Organism>>{pOrganism});
	mInitViewQueue.push_back(pOrganism);
}

void Simulation::addOrganismGroup(std::vector<std::shared_ptr<Organism>> pGroup)
{
	mOrganismGroups.push_back(pGroup);
	for (auto entity : pGroup)
	{
		mInitViewQueue.push_back(entity);
	}
}

void Simulation::addFood(std::shared_ptr<Food> pFood)
{
	mFoodSet.emplace(pFood);
	mInitViewQueue.push_back(pFood);
}

void Simulation::removeFood(std::shared_ptr<Food> pFood)
{
	mFoodSet.erase(pFood);
}

QQuickItem& Simulation::boardView() const
{
	return mBoard.mView;
}

qreal Simulation::deltaTime() const
{
	return QTime::currentTime().msecsTo(mInitialTime) / 1000.0;
}

Board& Simulation::board()
{
	return mBoard;
}

void Simulation::simulate() {}

void Simulation::train() {}

QTimer* Simulation::timer()
{
	return mTimer;
}

const int Simulation::ticksRemaining()
{
	return mTicksRemaining;
}

const int Simulation::stepsRemaining()
{
	return mStepsRemaining;
}

const int Simulation::generation()
{
	return mGeneration;
}

const int Simulation::score()
{
	return mScore;
}

void Simulation::scorePoint()
{
	mScore++;
}

std::vector<std::vector<std::shared_ptr<Organism>>>& Simulation::organismGroups()
{
	return mOrganismGroups; 
}

void Simulation::run()
{
	mScenario->updateUI();

	for (auto entity : mInitViewQueue)
	{
		entity->initView(*this);
		if (mAnimated)
			entity->mView->setVisible(true);
		else
			entity->mView->setVisible(false);
	}
	mInitViewQueue.clear();

	bool animate = mAnimateCheckBox->property("checked") == true;
	if (!animate && mAnimated)
	{
		for (auto item : boardView().childItems())
		{
			item->setVisible(false);
		}
		mTimer->setInterval(0);
		mAnimated = false;
	}
	else if (animate && !mAnimated)
	{
		for (auto item : boardView().childItems())
		{
			item->setVisible(true);
		}
		mTimer->setInterval(M_TICK_DURATION);
		mAnimated = true;
	}

	for (auto item : boardView().childItems())
	{
		View* view = dynamic_cast<View*>(item);
		std::shared_ptr<Organism> organism = std::dynamic_pointer_cast<Organism>(view->mModel);
		if (organism)
			organism->move(*this);
	}

	if (!mTicksRemaining)
		mInitialTime = QTime::currentTime();
	mScenario->simulateTick();

	for (auto item : boardView().childItems())
	{
		View* view = dynamic_cast<View*>(item);
		std::shared_ptr<Organism> organism = std::dynamic_pointer_cast<Organism>(view->mModel);
		if (organism)
			organism->simulate(*this);
	}

	for (auto item : boardView().childItems())
	{
		View* view = dynamic_cast<View*>(item);
		std::shared_ptr<Organism> organism = std::dynamic_pointer_cast<Organism>(view->mModel);
		if (organism)
			organism->detectCollisions(*this);
	}

	mScenario->simulateStep();

	for (auto view : View::mDeletionQueue)
	{
		if (std::dynamic_pointer_cast<Food>(view->mModel))
		{
			mFoodSet.erase(std::dynamic_pointer_cast<Food>(view->mModel));
		}
		else
		{
			int i = 0;
			for (auto& group : mOrganismGroups)
			{
				int j = 0;
				for (auto& organism : group)
				{
					if (organism == std::dynamic_pointer_cast<Organism>(view->mModel))
						group.erase(group.begin() + j);
					else
						j++;
				}
				if (!group.size())
					mOrganismGroups.erase(mOrganismGroups.begin() + i);
				else
					i++;
			}
		}
		view->deleteLater();
	}
	View::mDeletionQueue.clear();
}

void Simulation::start()
{
	View::mDeletionQueue.clear();
	mFoodSet.clear();
	mOrganismGroups.clear();
	mInitViewQueue.clear();
	mGeneration++;
	mScore = 0;

	mTicksRemaining = M_TICKS_PER_STEP;
	mStepsRemaining = M_STEPS_PER_ROUND;
	mScenario->startRound();

	mTimer->start();
	if (mAnimated)
	{
		mAnimateCheckBox->setProperty("checked", Qt::Checked);
		mTimer->setInterval(M_TICK_DURATION);
	}
	else
	{
		mAnimateCheckBox->setProperty("checked", Qt::Unchecked);
		mTimer->setInterval(0);
	}
}

void Simulation::init()
{
	mAnimateCheckBox->setProperty("checked", Qt::Checked);
	mAnimated = true;
	mTimer = new QTimer();
	connect(mTimer, SIGNAL(timeout()), this, SLOT(run()));

	start();
}

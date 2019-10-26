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
#include "CircleTrainingScenario.h"
#include "View.h"
#include "Model.h"
#include "Entity.h"
#include "Creature.h"
#include "Food.h"
#include "NeuralNetwork.h"

Simulation::Simulation(QQuickItem* pParent, Mode pMode)
	: mMode(pMode),
	  mContainer(*pParent),
	  mBoard(Board(*mContainer.findChild<QQuickItem*>("board"))),
	  mScenario(std::make_shared<CircleTrainingScenario>(CircleTrainingScenario(this,
		  nnScorePair(Organism::loadBrain("output\\saved\\366"),
		  -std::numeric_limits<qreal>::infinity())))),
	  M_TICK_DURATION(50),
	  M_TICKS_PER_STEP(5),
	  M_STEPS_PER_ROUND(500),
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
		try
		{
			View* view = dynamic_cast<View*>(item);
			std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(view->mModel);
			entity->move(*this);
		}
		catch (const std::exception & e)
		{
			std::cout << "An exception was caught with message '" << e.what() << "'\n";
		}
		catch (...)
		{
			std::cout << "An exception was caught while attempting to move an Entity\n";
		}
	}

	mScenario->simulateTick();

	if (mTicksRemaining)
	{
		mTicksRemaining--;
	}
	else
	{
		mScenario->simulateStep();
		mInitialTime = QTime::currentTime();
		mTicksRemaining = M_TICKS_PER_STEP;
	}

	for (auto item : boardView().childItems())
	{
		try
		{
			View* view = dynamic_cast<View*>(item);
			std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(view->mModel);
			entity->simulate(*this);
		}
		catch (const std::exception & e)
		{
			std::cout << "An exception was caught with message '" << e.what() << "'\n";
		}
	}

	for (auto item : boardView().childItems())
	{
		try
		{
			View* view = dynamic_cast<View*>(item);
			std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(view->mModel);
			entity->detectCollisions(*this);
		}
		catch (const std::exception & e)
		{
			std::cout << "An exception was caught with message '" << e.what() << "'\n";
		}
	}

	for (auto view : View::mDeletionQueue)
	{
		if (std::dynamic_pointer_cast<Food>(view->mModel))
		{
			mFoodSet.erase(std::dynamic_pointer_cast<Food>(view->mModel));
		}
		else
		{
			int i = 0;
			for (auto group : mOrganismGroups)
			{
				int j = 0;
				for (auto organism : group)
				{
					if (organism == std::dynamic_pointer_cast<Organism>(view->mModel))
					{
						group.erase(group.begin() + j);
						if (!group.size())
							mOrganismGroups.erase(mOrganismGroups.begin() + i);
						break;
					}
					i++;
				}
				j++;
			}
		}
		view->deleteLater();
	}
	View::mDeletionQueue.clear();

	if (mStepsRemaining)
	{
		mStepsRemaining--;
	}
	else
	{
		mScenario->endRound();
		start();
	}
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


	//switch (mMode)
	//{
	//	case Mode::debug:
	//	{
	//		QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
	//		NeuralNetwork nn;
	//		QPointF left = QPointF(mBoard.scaledWidth() / 2 - 60, mBoard.scaledHeight() / 2);
	//		QPointF right = QPointF(mBoard.scaledWidth() / 2 + 60, mBoard.scaledHeight() / 2);
	//		addFood(std::shared_ptr<Food>(new Food(*this, center)));
	//		addOrganism(std::shared_ptr<Organism>(new Creature(left, nn)));
	//		addOrganism(std::shared_ptr<Organism>(new Creature(right, nn)));
	//		break;
	//	}
	//	case Mode::train:
	//	{
	//		QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
	//		qreal radius = 15 * mBoard.cellSize() * SCALE_FACTOR;
	//		int entities = 100;
	//		int replicates = 4; // number of clones of each Entity

	//		std::shared_ptr<Food> food(new Food(*this, center));
	//		addFood(std::shared_ptr<Food>(food));

	//		for (int i = 0; i < entities; i++)
	//		{
	//			NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(pNeuralNetwork);
	//			//neuralNetwork = NeuralNetwork::mutateBasisWeights(neuralNetwork);
	//			std::vector<std::shared_ptr<Organism>> group = std::vector<std::shared_ptr<Organism>>();
	//			QColor groupColor = QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
	//			for (int j = 0; j < replicates; j++)
	//			{
	//				qreal angle = QRandomGenerator::global()->bounded(2 * M_PI / replicates) + j * 2 * M_PI / replicates;
	//				QPointF pos = QPointF(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
	//				group.push_back(std::shared_ptr<Organism>(new Creature(pos, neuralNetwork, groupColor)));
	//			}
	//			addOrganismGroup(group);
	//		}
	//		break;
	//	}
	//	case Mode::simulate:
	//	{
	//		break;
	//	}
	//	default:
	//	{
	//		break;
	//	}
	//}


}

void Simulation::init()
{
	mAnimateCheckBox->setProperty("checked", Qt::Checked);
	mAnimated = true;
	mTimer = new QTimer();
	connect(mTimer, SIGNAL(timeout()), this, SLOT(run()));

	start();
}

void Simulation::outputCounts()
{
	/*switch (mMode)
	{
		case Mode::debug:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* generationLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
			generationLabel->setProperty("text", "Generation: " + QString::number(mGeneration));
			QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
			scoreLabel->setProperty("text", "Score: " + QString::number(mScore));
			QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
			countLabel->setProperty("text", "Creatures: " + QString::number(Creature::mCount));
			break;
		}
		case Mode::train:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* generationLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
			generationLabel->setProperty("text", "Generation: " + QString::number(mGeneration));
			QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
			scoreLabel->setProperty("text", "Score: " + QString::number(mScore));
			QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
			countLabel->setProperty("text", "Creatures: " + QString::number(Creature::mCount));
			break;
		}
		case Mode::simulate:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
			countLabel->setProperty("text", "Red: " + QString::number(Creature::mCount));
			break;
		}
		default:
		{
			break;
		}
	}*/
}

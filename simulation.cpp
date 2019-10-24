#include "simulation.h"

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
#include "view.h"
#include "model.h"
#include "entity.h"
#include "creature.h"
#include "food.h"
#include "neuralnetwork.h"

Simulation::Simulation(QQuickItem* pParent, Mode pMode)
	: mMode(pMode),
	  mContainer(*pParent),
	  mBoard(Board(*mContainer.findChild<QQuickItem*>("board"))),
	  mBestNeuralNetwork(std::pair<NeuralNetwork, qreal>(NeuralNetwork(), -std::numeric_limits<qreal>::infinity())),
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
	init(mBestNeuralNetwork.first);
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

void Simulation::simulate()
{
	if (QRandomGenerator::global()->bounded(100) < Creature::mCreationChance)
	{
		addOrganism(std::shared_ptr<Organism>(new Creature(*this)));
	}
	if (QRandomGenerator::global()->bounded(100) < Food::mCreationChance)
	{
		addFood(std::shared_ptr<Food>(new Food(*this)));
	}
}

void Simulation::train()
{
	qreal progress = 1.0 - mStepsRemaining / static_cast<qreal>(M_STEPS_PER_ROUND);
	mContainer.findChild<QObject*>("progressBar")->setProperty("value", progress);
	if (mStepsRemaining)
	{
		mStepsRemaining--;
	}
	else
	{
		std::vector<std::pair<int, qreal>> groupResults;
		int i = 0;
		for (auto group : mOrganismGroups)
		{
			qreal sum = 0;
			for (auto organism : group)
			{
				sum += organism->mScore;
			}
			groupResults.push_back(std::pair<int, qreal>(i, sum));
			i++;
		}
		std::sort(groupResults.begin(), groupResults.end(), 
			[](const std::pair<int, qreal>& a, const std::pair<int, qreal>& b)
			{
				return (a.second > b.second);
			});

		std::cout << "\n-------------------------------------";
		for (auto group : groupResults)
		{
			std::cout << '\n' << group.second;
		}

		int first = groupResults[0].first;
		int second = groupResults.size() > 1 ? groupResults[1].first : -1;

		NeuralNetwork firstNN;
		NeuralNetwork secondNN;
		if (groupResults[0].second > mBestNeuralNetwork.second)
		{
			std::cout << "\nNew best neural network found\n";
			mBestNeuralNetwork = std::pair<NeuralNetwork, qreal>(mOrganismGroups[first][0]->mBrain, groupResults[0].second);
			int i = 0;
			for (auto weightMatrix : mBestNeuralNetwork.first.mWeights)
			{
				weightMatrix.save("output\\Theta" + std::to_string(i) + ".txt", arma::arma_ascii);
				i++;
			}
			firstNN = mOrganismGroups[first][0]->mBrain;
			secondNN = second == -1 ? NeuralNetwork() : mOrganismGroups[second][0]->mBrain;
		}
		else
		{
			firstNN = mBestNeuralNetwork.first;
			secondNN = mOrganismGroups[first][0]->mBrain;
		}
		NeuralNetwork newNN = NeuralNetwork::crossoverWeights(firstNN, secondNN);
		newNN = NeuralNetwork::crossoverBasisWeights(newNN, secondNN);

		for (auto item : boardView().childItems())
		{
			item->deleteLater();
		}
		Creature::mCount = 0;
		mTimer->stop();
		mStepsRemaining = M_STEPS_PER_ROUND;
		start(newNN);
	}
}

void Simulation::run()
{
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

	if (mTicksRemaining)
	{
		mTicksRemaining--;
	}
	else
	{
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

	switch (mMode)
	{
		case Mode::debug:
		{
			train();
			break;
		}
		case Mode::train:
		{
			train();
			break;
		}
		case Mode::simulate:
		{
			simulate();
			break;
		}
		default:
		{
			break;
		}
	}

	outputCounts();
}

void Simulation::start(const NeuralNetwork& pNeuralNetwork)
{
	View::mDeletionQueue.clear();
	mFoodSet.clear();
	mOrganismGroups.clear();
	mInitViewQueue.clear();
	mGeneration++;
	mScore = 0;

	mTicksRemaining = M_TICKS_PER_STEP;

	switch (mMode)
	{
		case Mode::debug:
		{
			QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
			NeuralNetwork nn;
			QPointF left = QPointF(mBoard.scaledWidth() / 2 - 60, mBoard.scaledHeight() / 2);
			QPointF right = QPointF(mBoard.scaledWidth() / 2 + 60, mBoard.scaledHeight() / 2);
			addFood(std::shared_ptr<Food>(new Food(*this, center)));
			addOrganism(std::shared_ptr<Organism>(new Creature(left, nn)));
			addOrganism(std::shared_ptr<Organism>(new Creature(right, nn)));
			break;
		}
		case Mode::train:
		{
			QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
			qreal radius = 15 * mBoard.cellSize() * SCALE_FACTOR;
			int entities = 40;
			int replicates = 10; // number of clones of each Entity

			std::shared_ptr<Food> food(new Food(*this, center));
			addFood(std::shared_ptr<Food>(food));

			for (int i = 0; i < entities; i++)
			{
				NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(pNeuralNetwork);
				//neuralNetwork = NeuralNetwork::mutateBasisWeights(neuralNetwork);
				std::vector<std::shared_ptr<Organism>> group = std::vector<std::shared_ptr<Organism>>();
				QColor groupColor = QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
				for (int j = 0; j < replicates; j++)
				{
					qreal angle = QRandomGenerator::global()->bounded(2 * M_PI / replicates) + j * 2 * M_PI / replicates;
					QPointF pos = QPointF(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
					group.push_back(std::shared_ptr<Organism>(new Creature(pos, neuralNetwork, groupColor)));
				}
				addOrganismGroup(group);
			}
			break;
		}
		case Mode::simulate:
		{
			break;
		}
		default:
		{
			break;
		}
	}

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

void Simulation::init(const NeuralNetwork& pNeuralNetwork)
{
	mAnimateCheckBox->setProperty("checked", Qt::Checked);
	mAnimated = true;
	mTimer = new QTimer();
	connect(mTimer, SIGNAL(timeout()), this, SLOT(run()));

	start(pNeuralNetwork);
}

void Simulation::outputCounts()
{
	switch (mMode)
	{
		case Mode::debug:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
			redLabel->setProperty("text", "Generation: " + QString::number(mGeneration));
			QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
			greenLabel->setProperty("text", "Score: " + QString::number(mScore));
			QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
			blueLabel->setProperty("text", "Entities: " + QString::number(Creature::mCount));
			break;
		}
		case Mode::train:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
			redLabel->setProperty("text", "Generation: " + QString::number(mGeneration));
			QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
			greenLabel->setProperty("text", "Score: " + QString::number(mScore));
			QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
			blueLabel->setProperty("text", "Entities: " + QString::number(Creature::mCount));
			break;
		}
		case Mode::simulate:
		{
			QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
			QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
			redLabel->setProperty("text", "Red: " + QString::number(Creature::mCount));
			break;
		}
		default:
		{
			break;
		}
	}
}

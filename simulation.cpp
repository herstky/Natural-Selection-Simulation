#include "simulation.h"

#include <QtWidgets/QLabel>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>
#include <QRandomGenerator>

#include <iostream>

#include "constants.h"
#include "view.h"
#include "model.h"
#include "entity.h"
#include "red.h"
#include "green.h"
#include "blue.h"
#include "food.h"
#include "neuralnetwork.h"

Simulation::Simulation(QQuickItem* pParent)
    : mMode(Mode::simulate),
	  mContainer(*pParent),
	  mBoard(Board(*mContainer.findChild<QQuickItem*>("board"))),
	  mScentSystem(ScentSystem(*this)),
	  mScentMap(coordMap()),
	  mDiffusionThread(QFuture<void>()),
      M_TICK_DURATION(50),
      M_TICKS_PER_STEP(5),
	  M_STEPS_PER_ROUND(100000), 
      mTicksRemaining(M_TICKS_PER_STEP),
	  mInitialTime(QTime::currentTime()),
	  mFoodSet(std::unordered_set<std::shared_ptr<Food>>()),
	  mOrganismGroups(std::vector<std::vector<std::shared_ptr<Organism>>>()),
	  mInitViewQueue(std::vector<std::shared_ptr<Entity>>()),
	  mScentQueue(coordMap())
{
	init();
}

Simulation::Simulation(QQuickItem* pParent, Mode pMode)
	: Simulation(pParent)
{
	mMode = pMode;
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

qreal Simulation::getScent(coordPair pCoords)
{
	return mScentMap.count(pCoords) ? mScentMap.at(pCoords) : 0;
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
	if (QRandomGenerator::global()->bounded(100) < Red::mCreationChance)
	{
		addOrganism(std::shared_ptr<Organism>(new Red(*this)));
	}
	if (QRandomGenerator::global()->bounded(100) < Food::mCreationChance)
	{
		addFood(std::shared_ptr<Food>(new Food(*this)));
	}
}

void Simulation::train()
{
	
}

void Simulation::run()
{
	for (auto entity : mInitViewQueue)
	{
		entity->initView(*this);
	}
	mInitViewQueue.clear();

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
		if (mDiffusionThread.isRunning())
			std::cout << "Warning, ScentSystem thread still running!\n";

		mDiffusionThread.waitForFinished();
		mScentMap = mScentSystem.mScentMap;
		mScentSystem.mAdditionQueue = mScentQueue;
		mScentQueue.clear();
		mDiffusionThread = QtConcurrent::run(QThreadPool::globalInstance(), &mScentSystem, &ScentSystem::update);

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

		mInitialTime = QTime::currentTime();
		mTicksRemaining = M_TICKS_PER_STEP;
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
		view->deleteLater();
	}
	View::mDeletionQueue.clear();

	switch (mMode)
	{
		case Mode::debug:
		{
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

void Simulation::init()
{
	Red::mCount = 0;
	Green::mCount = 0;
	Blue::mCount = 0;
	outputCounts();

	switch (mMode)
	{
		case Mode::debug:
		{
			QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
			addFood(std::shared_ptr<Food>(new Food(*this, center)));
			break;
		}
		case Mode::train:
		{
			QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
			qreal radius = 40 * mBoard.cellSize() * SCALE_FACTOR;
			int entities = 50;
			int replicates = 4; // number of clones of each Entity

			addFood(std::shared_ptr<Food>(new Food(*this, center)));
			for (int i = 0; i < entities; i++)
			{
				NeuralNetwork neuralNetwork;
				std::vector<std::shared_ptr<Organism>> group = std::vector<std::shared_ptr<Organism>>();
				for (int j = 0; j < replicates; j++)
				{
					qreal angle = QRandomGenerator::global()->bounded(2 * M_PI / replicates) + j * 2 * M_PI / replicates;
					QPointF pos = QPointF(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
					group.push_back(std::shared_ptr<Organism>(new Red(*this, pos, neuralNetwork)));
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

	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(run()));
	timer->start(M_TICK_DURATION);
}

void Simulation::outputCounts()
{
    QQuickItem* parent = static_cast<QQuickItem*>(mContainer.findChild<QObject*>("textRow"));
    QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
    redLabel->setProperty("text", "Red: " + QString::number(Red::mCount));
    QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
    greenLabel->setProperty("text", "Green: " + QString::number(Green::mCount));
    QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
    blueLabel->setProperty("text", "Blue: " + QString::number(Blue::mCount));
}


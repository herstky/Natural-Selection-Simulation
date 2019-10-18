#include "simulation.h"

#include <QtWidgets/QLabel>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>
#include <QRandomGenerator>

#include <iostream>

#include "constants.h"
#include "view.h"
#include "entity.h"
#include "red.h"
#include "green.h"
#include "blue.h"
#include "food.h"
#include "neuralnetwork.h"

Simulation::Simulation(QQuickItem* pParent)
    : mMode(Mode::simulate),
	  mContainer(*pParent),
	  mBoard(Board(mContainer.findChild<QQuickItem*>("board"))),
	  mScentSystem(ScentSystem(this)),
	  mDiffusionThread(QFuture<void>()),
      M_TICK_DURATION(50),
      M_TICKS_PER_STEP(5),
      mTicksRemaining(M_TICKS_PER_STEP),
	  mInitialTime(QTime::currentTime()),
	  mFoodSet(std::unordered_set<Food*>()),
	  mOrganismGroups(std::vector<std::vector<Organism*>*>())
{
	init();
}

Simulation::Simulation(QQuickItem* pParent, Mode pMode)
	: mMode(pMode),
	  mContainer(*pParent),
	  mBoard(Board(mContainer.findChild<QQuickItem*>("board"))),
	  mScentSystem(ScentSystem(this)),
	  mDiffusionThread(QFuture<void>()),
	  M_TICK_DURATION(50),
	  M_TICKS_PER_STEP(5),
	  mTicksRemaining(M_TICKS_PER_STEP),
	  mInitialTime(QTime::currentTime()),
	  mFoodSet(std::unordered_set<Food*>()),
	  mOrganismGroups(std::vector<std::vector<Organism*>*>())

{
	init();
}

Simulation::~Simulation() 
{
	for (auto it = mFoodSet.begin(); it != mFoodSet.end(); it++)
	{
		delete *it; // segfault. need to manage memory statically
	}
	mFoodSet.clear();

	for (auto group : mOrganismGroups)
	{
		for (auto entity : *group)
		{
			delete entity;
		}
		delete group;
	}
}

void Simulation::addOrganism(Organism* pOrganism)
{
	mOrganismGroups.push_back(new std::vector<Organism*>{pOrganism});
}

void Simulation::addOrganismGroup(std::vector<Organism*>* pGroup)
{
	mOrganismGroups.push_back(pGroup);
}

QQuickItem* Simulation::boardView() const
{
	return mBoard.mView;
}

qreal Simulation::deltaTime() const
{
	return QTime::currentTime().msecsTo(mInitialTime) / 1000.0;
}

Board* Simulation::board()
{
	return &mBoard;
}

void Simulation::simulate()
{
	if (QRandomGenerator::global()->bounded(100) < Red::mCreationChance)
	{
		addOrganism(new Red(*this));
	}
	if (QRandomGenerator::global()->bounded(100) < Food::mCreationChance)
	{
		new Food(*this);
	}
}

void Simulation::train()
{
	
}

void Simulation::run()
{
	for (auto item : boardView()->childItems())
	{
		try
		{
			View* view = dynamic_cast<View*>(item);
			Entity* entity = dynamic_cast<Entity*>(&view->mModel);
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
			std::cout << "Warning, diffusion thread still running!\n";

		mDiffusionThread.waitForFinished();
		mDiffusionThread = QtConcurrent::run(QThreadPool::globalInstance(), &mScentSystem, &ScentSystem::update);

		for (auto item : boardView()->childItems())
		{
			try
			{
				View* view = dynamic_cast<View*>(item);
				Entity* entity = dynamic_cast<Entity*>(&view->mModel);
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

	for (auto item : boardView()->childItems())
	{
		try
		{
			View* view = dynamic_cast<View*>(item);
			Entity* entity = dynamic_cast<Entity*>(&view->mModel);
			entity->detectCollisions(*this);
		}
		catch (const std::exception & e)
		{
			std::cout << "An exception was caught with message '" << e.what() << "'\n";
		}
	}

	for (auto view : View::mDeletionQueue)
	{
		view->deleteLater();
	}
	View::mDeletionQueue = QList<View*>();

	switch (mMode)
	{
		case(Mode::simulate):
		{
			simulate();
			break;
		}
		case(Mode::train):
		{
			train();
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
		case Mode::simulate:
		{
			break;
		}

		case Mode::train:
		{
			QPointF center = QPointF(mBoard.scaledWidth() / 2, mBoard.scaledHeight() / 2);
			qreal radius = 40 * mBoard.cellSize() * SCALE_FACTOR;
			int entities = 25;
			int replicates = 4; // number of clones of each Entity

			new Food(*this, center);

			for (int i = 0; i < entities; i++)
			{
				NeuralNetwork neuralNetwork;
				std::vector<Organism*>* group = new std::vector<Organism*>();
				for (int j = 0; j < replicates; j++)
				{
					qreal angle = QRandomGenerator::global()->bounded(2 * M_PI);
					QPointF pos = QPointF(radius * cos(angle) + center.x(), radius * sin(angle) + center.y());
					group->push_back(new Red(*this, pos, neuralNetwork));
				}
				mOrganismGroups.push_back(group);
			}
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


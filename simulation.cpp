#include "simulation.h"

#include <QtWidgets/QLabel>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>

#include <iostream>

#include "view.h"
#include "entity.h"
#include "red.h"
#include "green.h"
#include "blue.h"
#include "food.h"

Simulation::Simulation(QQuickItem* pParent)
    : mContainer(*pParent),
	  mBoard(Board(mContainer.findChild<QQuickItem*>("board"))),
	  mScentSystem(ScentSystem(this)),
	  mDiffusionThread(QFuture<void>()),
      M_TICK_DURATION(50),
      M_TICKS_PER_STEP(5),
      mTicksRemaining(M_TICKS_PER_STEP),
	  mInitialTime(QTime::currentTime())
{
	new Red(*this);
	init();
}

Simulation::~Simulation() {}

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
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
		catch (...)
		{
			std::cout << "An exception was caught while attempting to move an Entity\n";
		}
    }

    if (QRandomGenerator::global()->bounded(100) < Red::mCreationChance)
    {
		new Red(*this);
    }
	if (QRandomGenerator::global()->bounded(100) < Food::mCreationChance)
	{
		new Food(*this);
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
		mDiffusionThread = QtConcurrent::run(QThreadPool::globalInstance(), mScentSystem, &ScentSystem::diffuse);
		
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

    outputCounts();
}

void Simulation::init()
{
	Red::mCount = 0;
	Green::mCount = 0;
	Blue::mCount = 0;

	outputCounts();
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


#include "simulation.h"
#include <QtWidgets/QLabel>

#include <iostream>

#include "view.h"
#include "entity.h"
#include "red.h"
#include "green.h"
#include "blue.h"
#include "food.h"

Simulation::Simulation(QQuickItem* parent)
    : mContainer(*parent),
	  mBoard(Board(mContainer.findChild<QQuickItem*>("board"))),
      M_TICK_DURATION(50),
      M_TICKS_PER_STEP(10),
      mTicksRemaining(M_TICKS_PER_STEP),
	  mInitialTime(QTime::currentTime())
{
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


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
    : container(*parent),
      TICK_DURATION(50),
      TICKS_PER_STEP(1),
      ticksRemaining(TICKS_PER_STEP)
{
    Red::count = 0;
    Green::count = 0;
    Blue::count = 0;

    outputCounts();
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(TICK_DURATION);
}

Simulation::~Simulation() {}

QQuickItem* Simulation::board() const
{
	return container.findChild<QQuickItem*>("board");
}

void Simulation::run()
{
	QList<QQuickItem*> list = board()->childItems();
    for (auto item : board()->childItems())
    {
        try
        {
			View* view = static_cast<View*>(item);
			Entity* entity = dynamic_cast<Entity*>(&view->model);
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

    if (ticksRemaining)
    {
        ticksRemaining--;
        return;
    }
	else
	{
		ticksRemaining = TICKS_PER_STEP;
	}

    if (QRandomGenerator::global()->bounded(100) < Red::creationChance)
    {
		new Red(*this);
    }
	if (QRandomGenerator::global()->bounded(100) < Food::creationChance)
	{
		new Food(*this);
	}

    for (auto item : board()->childItems())
    {
        try
        {
			View* view = static_cast<View*>(item);
			Entity* entity = dynamic_cast<Entity*>(&view->model);
			entity->simulate(*this);
        }
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
    }

	for (auto item : board()->childItems())
	{
		try
		{
			View* view = static_cast<View*>(item);
			Entity* entity = dynamic_cast<Entity*>(&view->model);
			entity->detectCollisions(*this);
		}
		catch (const std::exception & e)
		{
			std::cout << "An exception was caught with message '" << e.what() << "'\n";
		}
	}

    outputCounts();
}

void Simulation::outputCounts()
{
    QQuickItem* parent = static_cast<QQuickItem*>(container.findChild<QObject*>("textRow"));
    QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
    redLabel->setProperty("text", "Red: " + QString::number(Red::count));
    QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
    greenLabel->setProperty("text", "Green: " + QString::number(Green::count));
    QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
    blueLabel->setProperty("text", "Blue: " + QString::number(Blue::count));
}


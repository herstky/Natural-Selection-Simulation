#include "simulation.h"
#include <QtWidgets/QLabel>

#include <iostream>

#include "red.h"
#include "green.h"
#include "blue.h"

Simulation::Simulation(QQuickItem* board)
    : board(board),
      TICK_DURATION(50),
      TICKS_PER_STEP(1),
      ticksRemaining(TICKS_PER_STEP)
{
    Red::count = 0;
    Green::count = 0;
    Blue::count = 0;

    outputCounts(board);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(TICK_DURATION);
}

Simulation::~Simulation() {}

void Simulation::run()
{
    for (auto item : board->childItems())
    {
        try
        {
            static_cast<Creature*>(item)->move(*this);
        }
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
    }
    if (ticksRemaining)
    {
        ticksRemaining--;
        return;
    }
    if (QRandomGenerator::global()->bounded(100) < Red(board).creationChance)
    {
        Red* red = new Red(board);
        creatures.push_back(red);
    }
    for (auto item : board->childItems())
    {
        try
        {
            static_cast<Creature*>(item)->simulate(*this);
        }
        catch (const std::exception& e)
        {
            std::cout << "An exception was caught with message '" << e.what() << "'\n";
        }
    }
    ticksRemaining = TICKS_PER_STEP;
    outputCounts(board);
}

void Simulation::outputCounts(QQuickItem *board)
{
    QQuickItem* parent = static_cast<QQuickItem*>(board->parentItem()->findChild<QObject*>("textRow"));
    QObject* redLabel = static_cast<QObject*>(parent->findChild<QObject*>("redCountText"));
    redLabel->setProperty("text", "Red: " + QString::number(Red::count));
    QObject* greenLabel = static_cast<QObject*>(parent->findChild<QObject*>("greenCountText"));
    greenLabel->setProperty("text", "Green: " + QString::number(Green::count));
    QObject* blueLabel = static_cast<QObject*>(parent->findChild<QObject*>("blueCountText"));
    blueLabel->setProperty("text", "Blue: " + QString::number(Blue::count));
}

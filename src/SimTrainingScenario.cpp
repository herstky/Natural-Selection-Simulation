#include "SimTrainingScenario.h"

#include "Simulation.h"
#include "Creature.h"
#include "Food.h"

SimTrainingScenario::SimTrainingScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	  mBestNeuralNetwork(pBestNeuralNetwork),
	  mNextNeuralNetwork(mBestNeuralNetwork.first)
{
	pSimulation->mMode = Simulation::Mode::train;
}

void SimTrainingScenario::startRound() {}

void SimTrainingScenario::endRound() {}

void SimTrainingScenario::simulateTick()
{
	if (mSimulation->mTicksRemaining)
	{
		mSimulation->mTicksRemaining--;
	}
	else
	{
		mSimulation->mTicksRemaining = mSimulation->M_TICKS_PER_STEP;
	}
}

void SimTrainingScenario::simulateStep()
{
	if (QRandomGenerator::global()->bounded(100) < Creature::creationChance())
	{
		NeuralNetwork newNeuralNetwork = NeuralNetwork::mutateWeights(mBestNeuralNetwork.first);
		mSimulation->addOrganism(std::shared_ptr<Organism>(new Creature(*mSimulation, newNeuralNetwork)));
	}
	if (QRandomGenerator::global()->bounded(100) < Food::mCreationChance)
	{
		mSimulation->addFood(std::shared_ptr<Food>(new Food(*mSimulation)));
	}
}

void SimTrainingScenario::updateUI()
{
	QQuickItem* parent = static_cast<QQuickItem*>(mSimulation->mContainer.findChild<QObject*>("textRow"));
	QObject* generationLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
	generationLabel->setProperty("text", "Generation: " + QString::number(mSimulation->generation()));
	QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
	scoreLabel->setProperty("text", "Score: " + QString::number(mSimulation->score()));
	QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
	countLabel->setProperty("text", "Creatures: " + QString::number(Creature::count()));
}

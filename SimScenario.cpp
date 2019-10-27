#include "SimScenario.h"

#include "Simulation.h"
#include "Creature.h"
#include "Food.h"

SimScenario::SimScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	  mBestNeuralNetwork(pBestNeuralNetwork),
	  mNextNeuralNetwork(mBestNeuralNetwork.first)
{
	Creature::setCreationChance(20);
	Food::setCreationChance(20);
	mSimulation->mContainer.findChild<QQuickItem*>("progressColumn")->setVisible(false);
}

void SimScenario::startRound()
{

}

void SimScenario::endRound()
{

}

void SimScenario::simulateTick()
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

void SimScenario::simulateStep()
{
	if (QRandomGenerator::global()->bounded(100) < Creature::creationChance())
	{
		NeuralNetwork newNeuralNetwork = NeuralNetwork::mutateWeights(mBestNeuralNetwork.first);
		mSimulation->addOrganism(std::shared_ptr<Organism>(new Creature(*mSimulation, newNeuralNetwork)));
	}
	if (QRandomGenerator::global()->bounded(100) < Food::creationChance())
	{
		mSimulation->addFood(std::shared_ptr<Food>(new Food(*mSimulation)));
	}
}


void SimScenario::updateUI()
{
	QQuickItem* parent = static_cast<QQuickItem*>(mSimulation->mContainer.findChild<QObject*>("textRow"));
	QObject* creatureCountLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
	creatureCountLabel->setProperty("text", "Creatures: " + QString::number(Creature::count()));
	QObject* foodCountLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
	foodCountLabel->setProperty("text", "Food: " + QString::number(Food::count()));
	QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
	scoreLabel->setProperty("text", "Score: " + QString::number(mSimulation->score()));
}

void SimScenario::eat(Organism& pPredator, Entity& pPrey)
{
	pPredator.score() += pPredator.foodReward();
	mSimulation->scorePoint();

	pPredator.energyLevel() += pPrey.getMass() * pPrey.getEnergyContent();
	pPredator.energyLevel() = std::min(pPredator.energyLevel(), pPredator.energyCapacity());
	pPrey.die(*mSimulation);
}

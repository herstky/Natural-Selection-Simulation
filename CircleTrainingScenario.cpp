#include "CircleTrainingScenario.h"

#include <QRandomGenerator>
#include <QPointF>

#include "Food.h"
#include "Simulation.h"
#include "Creature.h"
#include "NeuralNetwork.h"

CircleTrainingScenario::CircleTrainingScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	  mBestNeuralNetwork(pBestNeuralNetwork),
	  mNextNeuralNetwork(mBestNeuralNetwork.first),
	  mGroupMap(std::unordered_map<int, NeuralNetwork>()),
	  mGroupScores(std::vector<std::pair<int, qreal>>()) 
{
	Organism::mStarvationPenalty = 100; // 5
	Organism::mOutOfBoundsPenalty = 0; // 0
	Organism::mNoScentsPenalty = 0; // 0
	Organism::mEnergyExpenditurePenalty = 0; // 200000000
	Organism::mFoodReward = 300; // 200
	Organism::mScentReward = 0; // 1
	Organism::mScentIncreaseReward = 10; // 10
	Organism::mScentDecreasePenalty = 20; // 20

	NeuralNetwork::mMutationChance = 20;
	NeuralNetwork::mSmallVarianceMagnitude = 1;
	NeuralNetwork::mLargeVarianceMagnitude = 100;
	NeuralNetwork::mLargeVarianceChance = 0;
}

void CircleTrainingScenario::startRound()
{
	QPointF center = QPointF(mSimulation->board().widthP() / 2, mSimulation->board().heightP() / 2);
	qreal radius = 15 * mSimulation->board().cellSize() * SCALE_FACTOR;
	int entities = 20;
	int replicates = 20; // number of clones of each Entity

	std::shared_ptr<Food> food(new Food(*mSimulation, center));
	mSimulation->addFood(food);

	for (int i = 0; i < entities; i++)
	{
		NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(mNextNeuralNetwork);
		neuralNetwork = NeuralNetwork::mutateBasisWeights(neuralNetwork);
		mGroupScores.push_back(std::pair<int, qreal>(i, 0));
		std::vector<std::shared_ptr<Organism>> group;
		mGroupMap[i] = neuralNetwork;
		QColor groupColor = QColor(QRandomGenerator::global()->bounded(255),
			QRandomGenerator::global()->bounded(255),
			QRandomGenerator::global()->bounded(255));
		for (int j = 0; j < replicates; j++)
		{
			qreal angle = QRandomGenerator::global()->bounded(2 * M_PI / replicates) + j * 2 * M_PI / replicates;
			QPointF pos = QPointF(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
			std::shared_ptr<Organism> creature(new Creature(pos, neuralNetwork, groupColor));
			creature->mKey = i;
			group.push_back(std::shared_ptr<Organism>(creature));
		}
		mSimulation->addOrganismGroup(group);
	}
	mGroupScores.resize(mSimulation->organismGroups().size());
}

void CircleTrainingScenario::endRound() 
{
	for (auto group : mSimulation->organismGroups())
	{
		for (auto organism : group)
		{
			mGroupScores[organism->mKey].second += organism->score();
		}
	}

	qreal sum = 0;
	for (auto group : mGroupScores)
	{
		sum += group.second;
	}

	std::sort(mGroupScores.begin(), mGroupScores.end(),
		[](const std::pair<int, qreal>& a, const std::pair<int, qreal>& b)
		{
			return (a.second > b.second);
		});

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Generation: " << mSimulation->generation() << std::endl;
	std::cout << "Current high score: " << mBestNeuralNetwork.second << std::endl;
	std::cout << "High score: " << mGroupScores[0].second << std::endl;
	std::cout << "Low score: " << mGroupScores[mGroupScores.size() - 1].second << std::endl;
	std::cout << "Average score: " << sum / mGroupScores.size() << std::endl;

	int first = mGroupScores[0].first;
	int second = mGroupScores.size() > 1 ? mGroupScores[1].first : -1;

	NeuralNetwork firstNN;
	NeuralNetwork secondNN;
	NeuralNetwork bestNN = mGroupMap[first];

	if (mGroupScores[0].second > mBestNeuralNetwork.second)
	{
		std::cout << "\nNew best neural network found!" << std::endl;
		//mBestNeuralNetwork = std::pair<NeuralNetwork, qreal>(mSimulation->organismGroups()[first][0]->mBrain, mGroupScores[0].second);
		mBestNeuralNetwork = std::pair<NeuralNetwork, qreal>(bestNN, mGroupScores[0].second);
		firstNN = bestNN;
		secondNN = second == -1 ? NeuralNetwork() : mGroupMap[second];
		int i = 0;
		for (auto weightMatrix : mBestNeuralNetwork.first.weights())
		{
			weightMatrix.save("output\\Theta" + std::to_string(i) + ".txt", arma::arma_ascii);
			i++;
		}
	}
	else
	{
		firstNN = mBestNeuralNetwork.first;
		secondNN = bestNN;
	}
	NeuralNetwork newNN = NeuralNetwork::crossoverWeights(firstNN, secondNN);
	newNN = NeuralNetwork::crossoverBasisWeights(newNN, secondNN);

	mNextNeuralNetwork = newNN;

	for (auto item : mSimulation->boardView().childItems())
	{
		item->deleteLater();
	}
	mSimulation->timer()->stop();
	mGroupScores.clear();
}

void CircleTrainingScenario::simulateTick() 
{
	if (mSimulation->mTicksRemaining)
	{
		mSimulation->mTicksRemaining--;
	}
	else
	{
		mSimulation->mTicksRemaining = mSimulation->M_TICKS_PER_STEP;
	}

	//if (Creature::count() == 0 && mSimulation->timer()->isActive())
	//{
	//	endRound();
	//	mSimulation->start();
	//}
}

void CircleTrainingScenario::simulateStep() 
{
	if (mSimulation->mStepsRemaining)
	{
		mSimulation->mStepsRemaining--;
	}
	else
	{
		endRound();
		mSimulation->start();
	}
}

void CircleTrainingScenario::updateUI()
{
	qreal progress = 1.0 - mSimulation->stepsRemaining() / static_cast<qreal>(mSimulation->M_STEPS_PER_ROUND);
	mSimulation->mContainer.findChild<QObject*>("progressBar")->setProperty("value", progress);
	QQuickItem* parent = static_cast<QQuickItem*>(mSimulation->mContainer.findChild<QObject*>("textRow"));
	QObject* generationLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
	generationLabel->setProperty("text", "Generation: " + QString::number(mSimulation->generation()));
	QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
	countLabel->setProperty("text", "Creatures: " + QString::number(Creature::count()));
	QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
	scoreLabel->setProperty("text", "Score: " + QString::number(mSimulation->score()));
}

void CircleTrainingScenario::move(Organism& pOrganism)
{
	pOrganism.move(*mSimulation);
	pOrganism.score() -= Organism::mStarvationPenalty * mSimulation->M_TICK_DURATION / 1000.0;
}

void CircleTrainingScenario::eat(Organism& pPredator, Entity& pPrey)
{
	pPredator.score() += pPredator.foodReward();
	mSimulation->scorePoint();

	pPredator.energyLevel() += pPrey.getMass() * pPrey.getEnergyContent();
	pPredator.energyLevel() = std::min(pPredator.energyLevel(), pPredator.energyCapacity());
	die(pPredator);
}

void CircleTrainingScenario::expendEnergy(Organism& pOrganism) {}


void CircleTrainingScenario::die(Organism& pOrganism)
{
	mGroupScores[pOrganism.mKey].second += pOrganism.score();
	pOrganism.die(*mSimulation);
}
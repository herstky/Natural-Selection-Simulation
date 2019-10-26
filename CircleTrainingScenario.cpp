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
	  mNextNeuralNetwork(mBestNeuralNetwork.first) 
{
	pSimulation->mMode = Simulation::Mode::train;
}

void CircleTrainingScenario::startRound()
{
	QPointF center = QPointF(mSimulation->board().scaledWidth() / 2, mSimulation->board().scaledHeight() / 2);
	qreal radius = 15 * mSimulation->board().cellSize() * SCALE_FACTOR;
	int entities = 20;
	int replicates = 20; // number of clones of each Entity

	std::shared_ptr<Food> food(new Food(*mSimulation, center));
	mSimulation->addFood(std::shared_ptr<Food>(food));

	for (int i = 0; i < entities; i++)
	{
		NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(mNextNeuralNetwork);
		//neuralNetwork = NeuralNetwork::mutateBasisWeights(neuralNetwork);
		std::vector<std::shared_ptr<Organism>> group = std::vector<std::shared_ptr<Organism>>();
		QColor groupColor = QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
		for (int j = 0; j < replicates; j++)
		{
			qreal angle = QRandomGenerator::global()->bounded(2 * M_PI / replicates) + j * 2 * M_PI / replicates;
			QPointF pos = QPointF(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
			group.push_back(std::shared_ptr<Organism>(new Creature(pos, neuralNetwork, groupColor)));
		}
		mSimulation->addOrganismGroup(group);
	}
}

void CircleTrainingScenario::endRound() 
{
	std::vector<std::pair<int, qreal>> groupResults;
	int i = 0;
	for (auto group : mSimulation->organismGroups())
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
		mBestNeuralNetwork = std::pair<NeuralNetwork, qreal>(mSimulation->organismGroups()[first][0]->mBrain, groupResults[0].second);
		int i = 0;
		for (auto weightMatrix : mBestNeuralNetwork.first.mWeights)
		{
			weightMatrix.save("output\\Theta" + std::to_string(i) + ".txt", arma::arma_ascii);
			i++;
		}
		firstNN = mSimulation->organismGroups()[first][0]->mBrain;
		secondNN = second == -1 ? NeuralNetwork() : mSimulation->organismGroups()[second][0]->mBrain;
	}
	else
	{
		firstNN = mBestNeuralNetwork.first;
		secondNN = mSimulation->organismGroups()[first][0]->mBrain;
	}
	NeuralNetwork newNN = NeuralNetwork::crossoverWeights(firstNN, secondNN);
	newNN = NeuralNetwork::crossoverBasisWeights(newNN, secondNN);

	for (auto item : mSimulation->boardView().childItems())
	{
		item->deleteLater();
	}
	Creature::mCount = 0;
	mSimulation->timer()->stop();
}

void CircleTrainingScenario::simulateStep() {}

void CircleTrainingScenario::simulateTick() {}

void CircleTrainingScenario::updateUI()
{
	qreal progress = 1.0 - mSimulation->stepsRemaining() / static_cast<qreal>(mSimulation->M_STEPS_PER_ROUND);
	mSimulation->mContainer.findChild<QObject*>("progressBar")->setProperty("value", progress);
	QQuickItem* parent = static_cast<QQuickItem*>(mSimulation->mContainer.findChild<QObject*>("textRow"));
	QObject* generationLabel = static_cast<QObject*>(parent->findChild<QObject*>("label1"));
	generationLabel->setProperty("text", "Generation: " + QString::number(mSimulation->generation()));
	QObject* scoreLabel = static_cast<QObject*>(parent->findChild<QObject*>("label2"));
	scoreLabel->setProperty("text", "Score: " + QString::number(mSimulation->score()));
	QObject* countLabel = static_cast<QObject*>(parent->findChild<QObject*>("label3"));
	countLabel->setProperty("text", "Creatures: " + QString::number(Creature::mCount));
}
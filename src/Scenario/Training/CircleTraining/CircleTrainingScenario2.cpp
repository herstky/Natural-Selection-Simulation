#include "Scenario/Training/CircleTraining/CircleTrainingScenario2.h"

#include <QRandomGenerator>
#include <QPointF>

#include "Model/Entity/Food.h"
#include "Simulation.h"
#include "Model/Entity/Organism/StrongCreature.h"
#include "NeuralNetwork.h"

CircleTrainingScenario2::CircleTrainingScenario2(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: CircleTraining(pSimulation, pBestNeuralNetwork)
{
	Organism::mStarvationPenalty = 50; // 5
	Organism::mOutOfBoundsPenalty = 0; // 0
	Organism::mNoScentsPenalty = 0; // 0
	Organism::mEnergyExpenditurePenalty = 200000000;
	Organism::mFoodReward = 300; // 200
	Organism::mScentReward = 0; // 1
	Organism::mScentIncreaseReward = 0; // 10
	Organism::mScentDecreasePenalty = 0; // 20

	NeuralNetwork::mMutationChance = 20;
	NeuralNetwork::mSmallVarianceMagnitude = 1;
	NeuralNetwork::mLargeVarianceMagnitude = 100;
	NeuralNetwork::mLargeVarianceChance = 0;
}
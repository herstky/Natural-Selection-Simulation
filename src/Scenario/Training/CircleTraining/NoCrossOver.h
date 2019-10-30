#pragma once

#include "Scenario/Training/CircleTraining/CircleTraining.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"

// This class is the same as CircleTraining except it doesn't cross over the neural network
// weights. The fittest neural network is retained and mutated for each generation.  
class NoCrossOver : public CircleTraining
{
public:
	NoCrossOver(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void endRound() override;
};


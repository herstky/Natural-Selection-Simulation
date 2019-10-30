#pragma once

#include "CircleTraining.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"
#include "StrongCreature.h"

class CircleTrainingScenario3 : public CircleTraining
{
public:
	using CreatureClass = StrongCreature;
	CircleTrainingScenario3(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void endRound() override;

private:
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
	std::unordered_map<int, NeuralNetwork> mGroupMap;
	std::vector<std::pair<int, qreal>> mGroupScores;
};


#pragma once

#include "Scenario.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"

class CircleTrainingScenario2 : public Scenario
{
public:
	CircleTrainingScenario2(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void simulateTick() override;
	virtual void simulateStep() override;
	virtual void updateUI() override;
	virtual void move(Organism& pOrganism) override;
	virtual void eat(Organism& pPredator, Entity& pPrey) override;
	virtual void die(Organism& pOrganism) override;

private:
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
	std::unordered_map<int, NeuralNetwork> mGroupMap;
	std::vector<std::pair<int, qreal>> mGroupScores;
};


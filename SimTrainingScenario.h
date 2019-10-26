#pragma once

#include "Scenario.h"

#include <QtGlobal>

#include "NeuralNetwork.h"

class Simulation;

class SimTrainingScenario : public Scenario
{
public:
	SimTrainingScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void simulateStep() override;
	virtual void simulateTick() override;
	virtual void updateUI() override;

private:
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
};


#pragma once
#include "Scenario.h"

#include "NeuralNetwork.h"

class Simulation;

class DebugScenario :
	public Scenario
{
public:
	DebugScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void simulateStep() override;
	virtual void simulateTick() override;
	virtual void updateUI() override;
	virtual void eat(Organism& pPredator, Entity& pPrey) override;

	virtual void move(Organism& pOrganism);
	virtual void eat(Organism& pOrganism);

private:
	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
};


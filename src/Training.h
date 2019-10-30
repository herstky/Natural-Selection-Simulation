#pragma once

#include "Scenario.h"

#include "NeuralNetwork.h"
#include "Creature.h"

class Training : public Scenario
{
public:
	using CreatureClass = Creature;
protected:
	Training(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);
	virtual NeuralNetwork generateNeuralNetwork();

	std::pair<NeuralNetwork, qreal> mBestNeuralNetwork;
	NeuralNetwork mNextNeuralNetwork;
};
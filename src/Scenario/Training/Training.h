#pragma once

#include "Scenario/Scenario.h"

#include "NeuralNetwork.h"
#include "Model/Entity/Organism/Creature.h"

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
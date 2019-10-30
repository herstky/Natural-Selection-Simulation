#pragma once

#include "Scenario/Training/CircleTraining/CircleTraining.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"
#include "Model/Entity/Organism/WeakCreature.h"

class Simulation;

class CircleTrainingScenario : public CircleTraining
{
public:
	using CreatureClass = WeakCreature;
	CircleTrainingScenario(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void endRound() override;
	
protected:
	virtual NeuralNetwork generateNeuralNetwork() override;
};

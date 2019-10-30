#pragma once

#include "Scenario/Training/CircleTraining/CircleTraining.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"
#include "Model/Entity/Organism/StrongCreature.h"

// This class is currently the same as CircleTraining

class CircleTrainingScenario2 : public CircleTraining
{
public:
	using CreatureClass = StrongCreature;
	CircleTrainingScenario2(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);
};


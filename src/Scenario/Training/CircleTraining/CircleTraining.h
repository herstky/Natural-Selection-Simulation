#pragma once

#include "Scenario/Training/Training.h"

#include <utility>

#include <QPointF>

#include "Model/Entity/Organism/Organism.h"
#include "NeuralNetwork.h"

class Simulation;

// This training scenario spawns creatures in a circle around a food entity in the center. 
// Creatures are spawned in groups where every member of a group has a copy of the exact
// same neural network. Members of a group are evenly distributed around the circle to 
// avoid biasing the neural networks based on the creature's position relative to the food. 
// This class crosses over the overall top performing neural network with the next best
// in the current generation. 
class CircleTraining : public Training
{
public:
	CircleTraining(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void updateUI() override;

protected:
	qreal mSpawnRadius;
	int mNumGroups;
	int mNumReplicates;
	std::unordered_map<int, NeuralNetwork> mGroupMap;
	std::vector<std::pair<int, qreal>> mGroupScores;
};
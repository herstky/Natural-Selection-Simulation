#pragma once

#include "Scenario/Training/Training.h"

#include <utility>

#include "Model/Entity/Organism/StrongCreature.h"
#include "NeuralNetwork.h"

class Simulation;

class CircleTraining : public Training
{
public:
	using CreatureClass = StrongCreature;
	CircleTraining(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);

	virtual void startRound() override;
	virtual void endRound() override;
	virtual void simulateTick() override;
	virtual void simulateStep() override;
	virtual void updateUI() override;

protected:
	qreal mSpawnRadius;
	int mNumGroups;
	int mNumReplicates;
	std::unordered_map<int, NeuralNetwork> mGroupMap;
	std::vector<std::pair<int, qreal>> mGroupScores;
};
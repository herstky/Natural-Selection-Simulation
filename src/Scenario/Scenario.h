#pragma once

#include <memory>
#include <vector>
#include <utility>

#include <QtCore>

class Simulation; 
class Organism;
class Entity;

class Scenario
{
public:
	Scenario(Simulation* pSimulation);

	virtual void startRound() = 0;
	virtual void endRound() = 0;
	virtual void simulateTick();
	virtual void simulateStep();
	virtual void updateUI() = 0;

	void addKeyScore(std::pair<int, qreal> pPair);
	
protected:
	Simulation* mSimulation;
	std::vector<std::pair<int, qreal>> mKeyScore; // Multi-function vector for mapping Creature.mKey to Creature.mScore
};


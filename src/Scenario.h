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
	virtual void simulateStep() = 0;
	virtual void simulateTick() = 0;
	virtual void updateUI() = 0;

	inline void addKeyScore(std::pair<int, qreal> pPair)
	{
		mKeyScore.push_back(pPair);
	}

	virtual void eat(Organism& pPredator, Entity& pPrey);
	virtual void die(Organism& pOrganism);
	virtual void move(Organism& pOrganism);
	virtual void simulate(Organism& pOrganism);
	virtual void expendEnergy(Organism& pOrganism);
	
protected:
	Simulation* mSimulation;
	std::vector<std::pair<int, qreal>> mKeyScore; // Multi-function vector for mapping Creature.mKey to Creature.mScore
};


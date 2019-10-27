#pragma once

#include <memory>

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

	virtual void eat(Organism& pPredator, Entity& pPrey);
	virtual void die(Organism& pOrganism);
	virtual void move(Organism& pOrganism);
	virtual void simulate(Organism& pOrganism);
	
protected:
	Simulation* mSimulation;
};


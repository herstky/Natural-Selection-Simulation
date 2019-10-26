#pragma once

#include <memory>

class Simulation; 

class Scenario
{
public:
	Scenario(Simulation* pSimulation);

	virtual void startRound() = 0;
	virtual void endRound() = 0;
	virtual void simulateStep() = 0;
	virtual void simulateTick() = 0;
	virtual void updateUI() = 0;

protected:
	Simulation* mSimulation;
};


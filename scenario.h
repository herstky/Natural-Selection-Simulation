#pragma once

#include <memory>

class Simulation; 

class Scenario
{
public:
	Scenario(Simulation& pSimulation);
	Scenario(Simulation& pSimulation, int pTicksPerStep, int pStepsPerRound);

	virtual void startup() = 0;
	virtual void simulateRound() = 0;
	virtual void simulateStep() = 0;
	virtual void simulateTick() = 0;

private:
	Simulation& mSimulation;
	int mTicksPerStep;
	int mStepsPerRound;
};


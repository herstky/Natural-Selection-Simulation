#include "scenario.h"

#include "simulation.h"

Scenario::Scenario(Simulation& pSimulation)
	: mSimulation(pSimulation),
      mTicksPerStep(5),
	  mStepsPerRound(250) {}

Scenario::Scenario(Simulation& pSimulation, int pTicksPerStep, int pStepsPerRound)
	: Scenario(pSimulation)
{
	mTicksPerStep = pTicksPerStep;
	mStepsPerRound = pStepsPerRound;
}

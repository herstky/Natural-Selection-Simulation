#include "Scenario.h"

#include "Simulation.h"
#include "Organism.h"
#include "Creature.h"
#include "Entity.h"

Scenario::Scenario(Simulation* pSimulation)
	: mSimulation(pSimulation) {}

void Scenario::eat(Organism& pPredator, Entity& pPrey)
{
	pPredator.eat(*mSimulation, pPrey);
}

void Scenario::die(Organism& pOrganism)
{
	pOrganism.die(*mSimulation);
}

void Scenario::move(Organism& pOrganism)
{
	pOrganism.move(*mSimulation);
}

void Scenario::simulate(Organism& pOrganism)
{
	pOrganism.simulate(*mSimulation);
}

void Scenario::expendEnergy(Organism& pOrganism)
{
	pOrganism.expendEnergy(*mSimulation);
}

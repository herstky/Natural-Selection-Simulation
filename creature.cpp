#include "creature.h"

#include "simulation.h"

unsigned int Creature::mCount = 0;
qreal Creature::mCreationChance = 2;

Creature::Creature()
{
	init();
}

Creature::Creature(const Simulation& pSimulation)
	: Organism(pSimulation, NeuralNetwork())
{
	init();
}

Creature::Creature(const QPointF& pPosition)
    : Organism(pPosition)
{
	init();
}

Creature::Creature(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Organism(pSimulation, pBrain)
{
	init();
}

Creature::Creature(const QPointF& pPosition, NeuralNetwork pBrain)
	: Organism(pPosition, pBrain)
{
	init();
}

Creature::Creature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Organism(pPosition, pBrain, pColor)
{
	init();
}

Creature& Creature::operator=(const Creature& pOther)
{
	return *this;
}

Creature::~Creature() {}

void Creature::replicate(const Simulation& pSimulation) {}

void Creature::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
	mCount--;
}

void Creature::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mReplicationChance = 7;
	mMutationChance = 10;
	mDeathChance = 8;
	mCount++;
}
#include "Creature.h"

#include "Simulation.h"

qreal Creature::mCreationChance = 2;
int Creature::mCount = 0;

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

Creature::~Creature() 
{
	mCount--;
}

void Creature::replicate(const Simulation& pSimulation) {}

void Creature::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
}

const qreal Creature::creationChance()
{
	return mCreationChance;
}

void Creature::setCreationChance(qreal pCreationChance)
{
	mCreationChance = pCreationChance;
}

const int Creature::count()
{
	return mCount;
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
#include "red.h"

#include "simulation.h"
#include "green.h"

unsigned int Red::mCount = 0;
qreal Red::mCreationChance = 50;

Red::Red()
{
	init();
}

Red::Red(const Simulation& pSimulation)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
	init();
}

Red::Red(const QPointF& pPosition)
    : Organism(pPosition)
{
	init();
}

Red::Red(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Organism(pSimulation, pBrain)
{
	init();
}


Red::Red(const Simulation& pSimulation, const QPointF& pPosition, NeuralNetwork pBrain)
	: Organism(pSimulation, pPosition, pBrain)
{
	init();
}

Red& Red::operator=(const Red& pOther)
{
	return *this;
}

Red::~Red() {}

void Red::replicate(const Simulation& pSimulation) {}

void Red::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
	mCount--;
}

void Red::init()
{
	mType = Entity::Type::predator;
	mShape = Model::Shape::ellipse;
	mColor = Qt::red;
	mCreationChance = 50;
	mReplicationChance = 7;
	mMutationChance = 10;
	mDeathChance = 8;
	mCount++;
}
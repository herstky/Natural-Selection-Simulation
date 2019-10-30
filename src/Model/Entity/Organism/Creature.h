#pragma once

#include "Model/Entity/Organism/Organism.h"

class Simulation;

class Creature : public Organism
{
public:
    Creature();
	Creature(const Simulation& pSimulation);
    Creature(const QPointF& pPosition);
	Creature(const Simulation& pSimulation, NeuralNetwork pBrain);
	Creature(const QPointF& pPosition, NeuralNetwork pBrain);
	Creature(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor);
    virtual ~Creature() override;

    void replicate(const Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;
	static const qreal creationChance();
	static void setCreationChance(qreal pCreationChance);
	static const int count();

protected:
	virtual void init() override;

private:
	Creature(const Creature& pOther) {}
	Creature& operator=(const Creature& pOther);
	static qreal mCreationChance;
	static int mCount;


};


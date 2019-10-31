#pragma once

#include <unordered_set>
#include <memory>

#include "Model/Entity/Entity.h"

class Simulation;

class Food : public Entity
{
	friend class Simulation;
	friend class SimTrainingScenario;
public:
	Food(Simulation& pSimulation);
	Food(Simulation& pSimulation, const QPointF& pPosition);
	virtual ~Food() override;

	void detectCollisions(Simulation& pSimulation) override;
	const qreal height() const override;
	const qreal width() const override;
	const qreal volume() const;
	virtual void simulate(Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;
	virtual qreal scent(const qreal& distance) override;
	
	static const qreal creationChance();
	static void setCreationChance(qreal pCreationChance);
	static const int count();

protected:
	virtual void init(Simulation& pSimulation);

private:	
	Food(const Food& pOther) : mContainer(nullptr) {}
	Food& operator=(const Food& pOther);

	static qreal mCreationChance;
	static int mCount; 
	std::unordered_set<std::shared_ptr<Food>>* mContainer;
};


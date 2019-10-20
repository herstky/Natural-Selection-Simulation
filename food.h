#pragma once

#include <unordered_set>
#include <memory>

#include "entity.h"

class Simulation;

class Food : public Entity
{
	friend class Simulation;

public:
	Food(Simulation& pSimulation);
	Food(Simulation& pSimulation, const QPointF& pPosition);
	//~Food();

	void detectCollisions(const Simulation& pSimulation) override;
	const qreal height() const override;
	const qreal width() const override;
	const qreal volume() const;
	virtual void emanateScent(Simulation& pSimulation) override; // DEBUG: Need to verify with multiple Food instances
	virtual void simulate(Simulation& pSimulation) override;
	virtual void die(const Simulation& pSimulation) override;

protected:
	virtual void init(Simulation& pSimulation);

private:	
	static unsigned int mCount;
	static qreal mCreationChance;
	qreal mScentStrength;
	std::unordered_set<std::shared_ptr<Food>>& mContainer;
};


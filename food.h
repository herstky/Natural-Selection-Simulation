#pragma once

#include "entity.h"

class Simulation;

class Food : public Entity
{
	friend class Simulation;

public:
	Food(const Simulation& pSimulation);
	Food(const Simulation& pSimulation, const QPointF& pPosition);
	~Food();

	void detectCollisions(const Simulation& pSimulation) override;
	const qreal height() const override;
	const qreal width() const override;
	const qreal volume() const;
	virtual void emanateScent(Simulation& pSimulation) override;
	virtual void simulate(Simulation& pSimulation) override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;
	
	qreal mScentStrength;

	virtual void init() override;
};


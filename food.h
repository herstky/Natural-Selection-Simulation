#pragma once

#include "entity.h"

class Simulation;

class Food : public Entity
{
	friend class Simulation;

public:
	Food(const Simulation& simulation);
	Food(const Simulation& simulation, const QPointF& position);
	~Food();

	void detectCollisions(const Simulation& simulation) override;
	qreal height() override;
	qreal width() override;
	qreal volume();
	virtual void emanateScent(Simulation& simulation) override;

private:
	static unsigned int mCount;
	static qreal mCreationChance;

	virtual void init() override;
};


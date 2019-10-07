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

protected:
	qreal mEnergyContent;
	qreal mMass;
	qreal mDensity;
	qreal mAspectRatio;
	qreal mDepth;

private:
	static unsigned int mCount;
	static qreal mCreationChance;
};


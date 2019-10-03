#pragma once

#include "entity.h"

class Simulation;

class Food : public Entity
{
public:
	Food(const Simulation& simulation);
	Food(const Simulation& simulation, const QPointF& position);
	~Food();

	qreal volume();
	qreal volume(qreal _mass);
	qreal calculateHeight();
	qreal calculateHeight(qreal _volume);
	qreal calculateWidth();
	qreal calculateWidth(qreal _volume);

	qreal getCreationChance();

	void simulate(const Simulation& simulation) override;
	void move(const Simulation& simulation) override;

protected:
	qreal creationChance;
	QColor color;
	qreal energyContent;
	qreal mass;
	qreal density;
	qreal aspectRatio;
	qreal depth;

private:
	static unsigned int count;
};


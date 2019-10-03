#pragma once

#include "model.h"

class Simulation;

class Entity : public Model
{
public:
	Entity(const Simulation& simulation);
	Entity(const Simulation& simulation, const QPointF& position);
	~Entity();
	
	virtual void simulate(const Simulation& simulation);
	virtual void move(const Simulation& simulation);
};


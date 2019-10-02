#pragma once

#include "model.h"

class Simulation;

class Entity : public Model
{
public:
	Entity();
	~Entity();
	
protected:
	virtual void simulate(Simulation& simulation) = 0;
	virtual void move(Simulation& simulation) = 0;
};


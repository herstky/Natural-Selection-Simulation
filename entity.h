#pragma once

#include "model.h"

class Simulation;

class Entity : public Model
{
	friend class Simulation;

public:
	enum class Type { none, predator, prey };
	Entity(const Simulation& simulation);
	Entity(const Simulation& simulation, const QPointF& position);
	virtual ~Entity() override;
	
	virtual void simulate(const Simulation& simulation);
	virtual void move(const Simulation& simulation);
	virtual void detectCollisions(const Simulation& simulation);
	virtual void collide(const Simulation& simulation, Entity& other);
	Type getType();
	qreal getEnergyContent();
	qreal getMass();
	qreal getDensity();
	qreal getAspectRatio();
	qreal getDepth();

protected:
	Type mType;
	qreal mEnergyContent; // kJ/kg
	qreal mMass; // kg
	qreal mDensity; // kg/m^3
	qreal mAspectRatio; // height/width
	qreal mDepth; // m
};


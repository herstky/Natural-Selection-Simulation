#include "Entity.h"

#include <iostream>

#include <QQuickItem>

#include "Simulation.h"
#include "View.h"
#include "Food.h"

Entity::Entity()
    : mType(Entity::Type::none),
	  mEnergyContent(100),
	  mMass(0.005),
	  mDensity(1500),
	  mAspectRatio(1),
	  mDepth(0.1) {}

Entity::Entity(const QPointF& pPosition)
	: Entity()
{
	mX = pPosition.x() / SCALE_FACTOR;
	mY = pPosition.y() / SCALE_FACTOR;
}

void Entity::simulate(Simulation& pSimulation) 
{
	emanateScent(pSimulation);
}

void Entity::train(Simulation& pSimulation)
{
	
}

void Entity::move(const Simulation& pSimulation) {}

void Entity::detectCollisions(Simulation& pSimulation)
{
	if (mStatus == Model::Status::dead)
	{
		return;
	}

	for (auto food : pSimulation.mFoodSet)
	{
		if (food->mStatus == Model::Status::dead)
		{
			continue;
		}

		//https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
		//Logic inverted for top and bottom sides due to direction of y axis.
		if (hitbox().left() < food->hitbox().right() && hitbox().right() > food->hitbox().left() &&
			hitbox().top() < food->hitbox().bottom() && hitbox().bottom() > food->hitbox().top())
		{
			collide(pSimulation, *food);
		}
	}
}

void Entity::collide(Simulation& pSimulation, Entity& pOther) {}

void Entity::emanateScent(Simulation& pSimulation) {}

Entity::Type Entity::getType()
{
	return mType;
}

qreal Entity::getEnergyContent()
{
	return mEnergyContent;
}

qreal Entity::getMass()
{
	return mMass;
}

qreal Entity::getDensity()
{
	return mDensity;
}

qreal Entity::getAspectRatio()
{
	return mAspectRatio;
}

qreal Entity::getDepth()
{
	return mDepth;
}

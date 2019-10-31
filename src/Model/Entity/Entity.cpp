#include "Model/Entity/Entity.h"

#include <iostream>

#include <QQuickItem>

#include "Simulation.h"
#include "View.h"
#include "Model/Entity/Food.h"

Entity::Entity()
    : M_SCENT_STRENGTH(1.0),
	  M_SCENT_DIFFUSIVITY(0.001),
	  M_SCENT_RETENTION(0.75),
	  mType(Entity::Type::none),
	  mPersistent(false),
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

Entity::~Entity() {}

Entity::Entity(const Entity& pOther)
	: Entity() {}

Entity& Entity::operator=(const Entity& pOther) 
{
	return *this;
}

void Entity::simulate(Simulation& pSimulation) {}

void Entity::train(Simulation& pSimulation) {}

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

void Entity::emanateScent() {}

qreal Entity::scent(const qreal& distance) 
{
	return 0;
}

Entity::Type Entity::getType()
{
	return mType;
}

void Entity::setPersistent(bool pPersistent)
{
	mPersistent = pPersistent;
}

bool Entity::persistent()
{
	return mPersistent;
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

#include "entity.h"

#include <iostream>

#include <QQuickItem>

#include "simulation.h"
#include "view.h"

Entity::Entity(const Simulation& simulation) 
	: Model(simulation),
	  mType(Entity::Type::none),
	  mEnergyContent(100),
	  mMass(0.005),
	  mDensity(1500),
	  mAspectRatio(1),
	  mDepth(0.1) {}

Entity::Entity(const Simulation& simulation, const QPointF& position)
	: Model(simulation, position),
	  mType(Entity::Type::none),
   	  mEnergyContent(100),
	  mMass(0.005),
	  mDensity(1500),
	  mAspectRatio(1),
	  mDepth(0.1) {}

Entity::~Entity() {}

void Entity::simulate(Simulation& simulation) 
{
	emanateScent(simulation);
}

void Entity::move(const Simulation& simulation) {}

void Entity::detectCollisions(const Simulation& simulation)
{
	if (mStatus == Model::Status::dead)
	{
		return;
	}

	QList<QQuickItem*> items = simulation.boardView()->childItems();
	for (auto item : items)
	{
		View* view = static_cast<View*>(item);
		Entity* entity = dynamic_cast<Entity*>(&view->mModel);
		if (entity == this || entity->mStatus == Model::Status::dead)
		{
			continue;
		}

		//https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
		//Logic inverted for top and bottom sides due to direction of y axis.
		//if (hitbox().left() < entity->hitbox().right() && hitbox().right() > entity->hitbox().left() &&
		//	hitbox().top() < entity->hitbox().bottom() && hitbox().bottom() > entity->hitbox().top())
		//{
		//	collide(simulation, *entity);
		//}
	}
}

void Entity::collide(const Simulation& simulation, Entity& other) {}

void Entity::emanateScent(Simulation& simulation) {}

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

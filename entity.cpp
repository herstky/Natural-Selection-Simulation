#include "entity.h"

#include <iostream>

#include <QQuickItem>

#include "simulation.h"
#include "view.h"

Entity::Entity(const Simulation& simulation) 
	: Model(simulation) {}

Entity::Entity(const Simulation& simulation, const QPointF& position)
	: Model(simulation, position) {}

Entity::~Entity() {}

void Entity::simulate(const Simulation& simulation) {}

void Entity::move(const Simulation& simulation) {}

void Entity::detectCollisions(const Simulation& simulation)
{
	QList<QQuickItem*> items = simulation.board()->childItems();
	for (auto item : items)
	{
		View* view = static_cast<View*>(item);
		Entity* entity = dynamic_cast<Entity*>(&view->model);
		if (entity == this)
		{
			continue;
		}

		//https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
		//Logic inverted for top and bottom sides due to direction of y axis.
		if (hitbox().left() < entity->hitbox().right() && hitbox().right() > entity->hitbox().left() &&
			hitbox().top() < entity->hitbox().bottom() && hitbox().bottom() > entity->hitbox().top())
		{
			entity->die(simulation);
		}
	}
}

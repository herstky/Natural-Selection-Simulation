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

		qreal a = hitbox().left();
		qreal b = entity->hitbox().right();
		qreal c = hitbox().right();
		qreal d = entity->hitbox().left();
		qreal e = hitbox().top();
		qreal f = entity->hitbox().bottom();
		qreal g = hitbox().bottom();
		qreal h = entity->hitbox().top();

		if (hitbox().left() < entity->hitbox().right() && hitbox().right() > entity->hitbox().left() &&
			hitbox().top() < entity->hitbox().bottom() && hitbox().bottom() > entity->hitbox().top())
		{
			std::cout << "Collision detected!\n";
		}
	}
}

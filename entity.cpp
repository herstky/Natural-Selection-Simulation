#include "entity.h"

Entity::Entity(const Simulation& simulation) 
	: Model(simulation) {}

Entity::Entity(const Simulation& simulation, const QPointF& position)
	: Model(simulation, position) {}

Entity::~Entity() {}

void Entity::simulate(const Simulation& simulation) {}

void Entity::move(const Simulation& simulation) {}

#include "model.h"

#include "simulation.h"
#include "view.h"

Model::Model()
	: status(alive),
	  color(Qt::black),
	  shape(rectangle),
	  height(0),
	  width(0),
	  x(0),
	  y(0) {}

Model::Model(const Simulation& simulation)
	: status(alive),
	  color(Qt::black),
	  shape(rectangle),
	  height(0),
	  width(0),
	  x(QRandomGenerator::global()->bounded(simulation.board()->width() - width)),
	  y(QRandomGenerator::global()->bounded(simulation.board()->width() - width)) 
{
	new View(simulation.board(), *this);
}

Model::Model(const Simulation& simulation, const QPointF& position) 
	: status(alive),
	  color(Qt::black),
	  shape(rectangle),
	  height(0),
	  width(0),
	  x(position.x()),
	  y(position.y()) 
{
	new View(simulation.board(), *this);
}

Model::~Model() {}
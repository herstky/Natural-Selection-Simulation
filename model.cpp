#include "model.h"

#include "simulation.h"
#include "view.h"

Model::Model(const Simulation& simulation)
	: status(Model::Status::alive),
	  color(Qt::black),
	  shape(Model::Shape::rectangle),
	  height(1),
	  width(1),
	  x(QRandomGenerator::global()->bounded(simulation.board()->width() - width)), // position is being set with initial height and width of 1
	  y(QRandomGenerator::global()->bounded(simulation.board()->height() - height)),
	  view(nullptr) {}

Model::Model(const Simulation& simulation, const QPointF& position) 
	: status(Model::Status::alive),
	  color(Qt::black),
	  shape(Model::Shape::rectangle),
	  height(1),
	  width(1),
	  x(position.x()),
	  y(position.y()),
	  view(nullptr) {}

Model::~Model() {}

void Model::initView(const Simulation& simulation)
{
	view = new View(simulation.board(), *this);
	view->init();
}
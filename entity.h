#pragma once

#include <QQuickPaintedItem>

class Simulation;
class Model;

class Entity : public QQuickPaintedItem
{
	Q_OBJECT
public:
	Entity(QQuickItem* parent = nullptr);
	~Entity();
	
	Model* model;

	void paint(QPainter* painter);

protected:
	friend class Simulation;
	QColor color;

	virtual void simulate(Simulation& simulation);
	virtual void move(Simulation& simulation);

};


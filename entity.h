#pragma once

#include <QQuickPaintedItem>

class Simulation;

class Entity : public QQuickPaintedItem
{
	Q_OBJECT
public:
	Entity(QQuickItem* parent = nullptr);
	~Entity();

	void paint(QPainter* painter) = 0;

protected:
	friend class Simulation;
	QColor color;

	virtual void simulate(Simulation& simulation) = 0;
	virtual void move(Simulation& simulation) = 0;

};


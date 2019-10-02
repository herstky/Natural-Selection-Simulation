#pragma once

#include <QQuickPaintedItem>

class Model;

class View : QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* parent = nullptr);
	View(QQuickItem* parent, Model& model);
	~View();

	void paint(QPainter* painter);

	const Model& model;

};


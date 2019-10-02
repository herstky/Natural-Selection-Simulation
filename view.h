#pragma once

#include <QQuickPaintedItem>

class Model;

class View : QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* parent = nullptr);
	~View();

	void paint(QPainter* painter);

	Model model;

};


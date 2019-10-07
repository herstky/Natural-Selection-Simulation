#pragma once

#include <QQuickPaintedItem>

class Model;

class View : public QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* parent, Model& model);
	~View();

	static QList<View*> deletionQueue;

	void init();

	void paint(QPainter* painter);

	Model& model;

};


#pragma once

#include <QQuickPaintedItem>

class Model;

class View : public QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* parent, Model& model);
	~View();

	static QList<View*> mDeletionQueue;

	void init();

	void paint(QPainter* painter);

	Model& mModel;

};


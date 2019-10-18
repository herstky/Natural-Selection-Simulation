#pragma once

#include <QQuickPaintedItem>

class Model;

class View : public QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* pParent, Model& pModel);

	static QList<View*> mDeletionQueue;

	void init();

	void paint(QPainter* pPainter);

	Model& mModel;
};


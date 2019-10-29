#pragma once

#include <QQuickPaintedItem>

#include <vector>
#include <memory>

class Model;

class View : public QQuickPaintedItem
{
	Q_OBJECT;
public:
	View(QQuickItem* pParent, std::shared_ptr<Model> pModel);

	static std::vector<View*> mDeletionQueue;

	void init();

	void paint(QPainter* pPainter);

	std::shared_ptr<Model> mModel;
};


#include "view.h"

#include <QPainter>

#include "model.h"

View::View(QQuickItem* parent = nullptr)
	: QQuickPaintedItem(parent), model(Model()) {}

View::View(QQuickItem* parent, Model& model)
	: QQuickPaintedItem(parent), model(model) {}

View::~View() {}

void View::paint(QPainter* painter)
{
	QBrush brush(model.color);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	
	switch (model.shape)
	{
	case Model::ellipse:
		painter->drawEllipse(contentsBoundingRect());
	case Model::rectangle:
		painter->drawRect(contentsBoundingRect());
	case Model::roundedRectangle:
		painter->drawRoundedRect(contentsBoundingRect(), 2, 2);
	default:
		painter->drawRect(contentsBoundingRect());
	}
}
#include "view.h"

#include <QPainter>

#include "model.h"
#include "constants.h"

View::View(QQuickItem* parent, Model& model)
	: QQuickPaintedItem(parent), model(model) 
{
	setHeight(SCALE_FACTOR * model.height);
	setWidth(SCALE_FACTOR * model.width);
	setZ(SCALE_FACTOR * 1);
	setOpacity(0.4);
	setFlag(QQuickItem::ItemHasContents);
}

View::~View() {}

void View::paint(QPainter* painter)
{
	setPosition(QPointF(model.x, model.y));

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
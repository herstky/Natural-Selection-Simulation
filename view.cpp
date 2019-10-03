#include "view.h"

#include <QPainter>

#include "model.h"
#include "constants.h"

View::View(QQuickItem* parent, Model& model)
	: QQuickPaintedItem(parent), model(model) 
{
	init();
}

View::~View() 
{
	//delete &model;
}

void View::init()
{
	setHeight(SCALE_FACTOR * model.height());
	setWidth(SCALE_FACTOR * model.width());
	setZ(SCALE_FACTOR * 1);
	setOpacity(0.4);
	setFlag(QQuickItem::ItemHasContents);
}

void View::paint(QPainter* painter)
{
	if (model.status == Model::Status::dead)
	{
		deleteLater();
		return;
	}
	
	setPosition(QPointF(model.x(), model.y()));

	QBrush brush(model.color);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	
	switch (model.shape)
	{
	case Model::Shape::ellipse:
		painter->drawEllipse(contentsBoundingRect());
		break;
	case Model::Shape::rectangle:
		painter->drawRect(contentsBoundingRect());
		break;
	case Model::Shape::roundedRectangle:
		painter->drawRoundedRect(contentsBoundingRect(), 2, 2);
		break;
	default:
		painter->drawRect(contentsBoundingRect());
	}
}
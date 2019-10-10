#include "view.h"

#include <QPainter>

#include "model.h"
#include "constants.h"

QList<View*> View::mDeletionQueue = QList<View*>();

View::View(QQuickItem* parent, Model& model)
	: QQuickPaintedItem(parent), mModel(model) {}

View::~View() 
{
	delete &mModel;
}

void View::init()
{
	setX(mModel.scaledX());
	setY(mModel.scaledY());
	setHeight(mModel.scaledHeight());
	setWidth(mModel.scaledWidth());
	setZ(1);
	setOpacity(0.4);
	setFlag(QQuickItem::ItemHasContents);
}

void View::paint(QPainter* painter)
{
	if (mModel.mStatus == Model::Status::dead)
	{
		return;
	}
	
	setPosition(QPointF(mModel.x(), mModel.y()));

	QBrush brush(mModel.mColor);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	
	switch (mModel.mShape)
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
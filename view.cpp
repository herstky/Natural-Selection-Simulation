#include "view.h"

#include <QPainter>

#include "model.h"
#include "constants.h"

QList<View*> View::mDeletionQueue = QList<View*>();

View::View(QQuickItem* pParent, Model& pModel)
	: QQuickPaintedItem(pParent), mModel(pModel) {}

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

void View::paint(QPainter* pPainter)
{
	if (mModel.mStatus == Model::Status::dead)
	{
		return;
	}
	
	setPosition(QPointF(mModel.scaledX(), mModel.scaledY()));

	QBrush brush(mModel.mColor);
	pPainter->setBrush(brush);
	pPainter->setPen(Qt::NoPen);
	pPainter->setRenderHint(QPainter::HighQualityAntialiasing);
	
	switch (mModel.mShape)
	{
	case Model::Shape::ellipse:
		pPainter->drawEllipse(contentsBoundingRect());
		break;
	case Model::Shape::rectangle:
		pPainter->drawRect(contentsBoundingRect());
		break;
	case Model::Shape::roundedRectangle:
		pPainter->drawRoundedRect(contentsBoundingRect(), 2, 2);
		break;
	default:
		pPainter->drawRect(contentsBoundingRect());
	}
}
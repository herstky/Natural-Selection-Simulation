#include "view.h"

#include <QPainter>

#include "model.h"
#include "constants.h"

std::vector<std::shared_ptr<View>> View::mDeletionQueue = std::vector<std::shared_ptr<View>>();

View::View(QQuickItem* pParent, std::shared_ptr<Model> pModel)
	: QQuickPaintedItem(pParent), mModel(pModel) {}

void View::init()
{
	setX(mModel->xP());
	setY(mModel->yP());
	setHeight(mModel->heightP());
	setWidth(mModel->widthP());
	setZ(1);
	setOpacity(0.4);
	setFlag(QQuickItem::ItemHasContents);
}

void View::paint(QPainter* pPainter)
{
	if (mModel->mStatus == Model::Status::dead)
	{
		return;
	}
	
	setPosition(QPointF(mModel->xP(), mModel->yP()));

	QBrush brush(mModel->mColor);
	pPainter->setBrush(brush);
	pPainter->setPen(Qt::NoPen);
	pPainter->setRenderHint(QPainter::HighQualityAntialiasing);
	
	switch (mModel->mShape)
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
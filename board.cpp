#include "board.h"

#include "constants.h"

Board::Board(QQuickItem* parent)
	: QQuickPaintedItem(parent),
	  color(Qt::lightGray),
	  cellSize(1),
	  rows(30),
	  columns(60)
{
	setHeight(300.0);
	setWidth(300.0);
	setPosition(QPointF(10, 10));
	setFlag(QQuickItem::ItemHasContents);
}

Board::Board(QQuickItem* parent, qreal cellSize, int rows, int columns)
	: QQuickPaintedItem(parent),
	  color(Qt::lightGray),
	  cellSize(cellSize),
	  rows(rows),
	  columns(columns)
{
	setHeight(SCALE_FACTOR * cellSize * rows);
	setWidth(SCALE_FACTOR * cellSize * columns);

	setPosition(QPointF(parent->width() / 2.0 - width() / 2.0, parent->height() / 2.0 - height() / 2.0));
	setFlag(QQuickItem::ItemHasContents);
}

Board::~Board() {}

void Board::paint(QPainter* painter)
{
	QBrush brush(color);
	painter->setBrush(brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	painter->drawRect(contentsBoundingRect());
}


#include "board.h"

#include "simulation.h"
#include "constants.h"

#include <iostream>

Board::Board(QQuickItem* pView) 
	: mView(pView),
	  mCellSize(0.003), 
	  mRows(150), 
	  mColumns(300)
{
	init();
}

Board::~Board() {}

QQuickItem* Board::view()
{
	return mView;
}

qreal Board::cellSize() const
{
	return mCellSize;
}

qreal Board::scaledCellSize() const
{
	return SCALE_FACTOR * mCellSize;
}

int Board::rows() const
{
	return mRows;
}

int Board::columns() const
{
	return mColumns;
}

qreal Board::height() const
{
	return cellSize() * rows();
}

qreal Board::scaledHeight() const
{
	return scaledCellSize() * rows();
}

qreal Board::width() const
{
	return cellSize() * columns();
}

qreal Board::scaledWidth() const
{
	return scaledCellSize() * columns();
}

void Board::init()
{
	mView->setHeight(scaledHeight());
	dynamic_cast<QQuickItem*>(mView->parent())->setWidth(scaledWidth());
}

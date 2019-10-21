#include "board.h"

#include "simulation.h"
#include "constants.h"

#include <iostream>

Board::Board(QQuickItem& pQQuickItem) 
	: mView(pQQuickItem),
	  mCellSize(0.0075), 
	  mRows(50), 
	  mColumns(100)
{
	init();
}

QQuickItem& Board::view()
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
	mView.setHeight(scaledHeight());
	dynamic_cast<QQuickItem*>(mView.parent())->setWidth(scaledWidth());
}

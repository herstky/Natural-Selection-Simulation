#include "Board.h"

#include "Simulation.h"
#include "constants.h"

Board::Board(QQuickItem& pQQuickItem) 
	: mView(pQQuickItem),
	  M_CELL_SIZE(0.0075), 
	  mRows(50), 
	  mColumns(50)
{
	init();
}

QQuickItem& Board::view()
{
	return mView;
}

qreal Board::cellSize() const
{
	return M_CELL_SIZE;
}

qreal Board::scaledCellSize() const
{
	return SCALE_FACTOR * M_CELL_SIZE;
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

qreal Board::heightP() const
{
	return scaledCellSize() * rows();
}

qreal Board::width() const
{
	return cellSize() * columns();
}

qreal Board::widthP() const
{
	return scaledCellSize() * columns();
}

void Board::init()
{
	mView.setHeight(heightP());
	dynamic_cast<QQuickItem*>(mView.parent())->setWidth(widthP());
	for (auto child : dynamic_cast<QQuickItem*>(mView.parent())->childItems())
	{
		child->setWidth(widthP());
	}
}

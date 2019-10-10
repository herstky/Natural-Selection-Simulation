#include "board.h"

#include "simulation.h"
#include "constants.h"

#include <iostream>

Board::Board(QQuickItem* view) 
	: mView(view),
	  mCellSize(0.001), 
	  mRows(300), 
	  mColumns(600)
{
	init();
}

Board::~Board() {}

QQuickItem* Board::view()
{
	return mView;
}

qreal Board::cellSize()
{
	return mCellSize;
}

qreal Board::scaledCellSize()
{
	return SCALE_FACTOR * mCellSize;
}

int Board::rows()
{
	return mRows;
}

int Board::columns()
{
	return mColumns;
}

qreal Board::height()
{
	return scaledCellSize() * rows();
}

qreal Board::width()
{
	return scaledCellSize() * columns();
}

std::vector<std::vector<qreal>>* Board::grid()
{
	return &mGrid;
}

void Board::init()
{
	mGrid = std::vector<std::vector<qreal>>(mRows, std::vector<qreal>(mColumns, 0));
	mView->setHeight(height());
	dynamic_cast<QQuickItem*>(mView->parent())->setWidth(width());
}

void Board::diffuseParticles(const Simulation& simulation)
{
	std::vector<std::vector<qreal>> incoming(rows(), std::vector<qreal>(columns(), 0));
	std::vector<std::vector<qreal>> outgoing(rows(), std::vector<qreal>(columns(), 0));

	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			std::vector<std::vector<int>> directions
			{ 
				{0, 1}, 
				{1, 0},
				{0, -1},
				{-1, 0}
			};

			for (auto direction : directions)
			{
				int m = i + direction[0];
				int n = j + direction[1];
				qreal molesTransferred; // -D * A * dphi/dx * dt [mol]
				if (m < 0 || m >= rows() || n < 0 || n >= columns())
				{
					molesTransferred = D_FOOD * (mGrid[i][j]) * simulation.deltaTime(); // A = 1 and dx = 1
					outgoing[i][j] += molesTransferred;
				}
				else
				{
					molesTransferred = D_FOOD * (mGrid[i][j] - mGrid[m][n]) * simulation.deltaTime();
					incoming[m][n] += molesTransferred;
					outgoing[i][j] += molesTransferred;
				}
			}
			// some particles exit system in positive z-direction
			outgoing[i][j] += D_FOOD * (mGrid[i][j]) * simulation.deltaTime(); 
		}
	}

	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			mGrid[i][j] += (incoming[i][j] - outgoing[i][j]);
		}
	}
}

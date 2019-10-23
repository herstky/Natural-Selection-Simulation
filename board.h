#pragma once

#include <QQuickItem>

#include <vector>

#include "view.h"

class Simulation;

class Board
{
public:
	friend class Food;
	friend class Simulation;

	Board(QQuickItem& pView);

	QQuickItem& view();
	qreal cellSize() const;
	qreal scaledCellSize() const;
	int rows() const;
	int columns() const;
	qreal height() const;
	qreal scaledHeight() const;
	qreal width() const;
	qreal scaledWidth() const;

	const qreal M_CELL_SIZE; // [m]

private:
	QQuickItem& mView;
	int mRows;
	int mColumns;

	void init();
};


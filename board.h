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

	Board(std::shared_ptr<QQuickItem> pView);

	std::shared_ptr<QQuickItem> view();
	qreal cellSize() const;
	qreal scaledCellSize() const;
	int rows() const;
	int columns() const;
	qreal height() const;
	qreal scaledHeight() const;
	qreal width() const;
	qreal scaledWidth() const;

private:
	std::shared_ptr<QQuickItem> mView;
	qreal mCellSize; // [m]
	int mRows;
	int mColumns;

	void init();
};


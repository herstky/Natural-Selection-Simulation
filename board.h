#pragma once

#include <QQuickItem>

#include <vector>

class Simulation;

class Board
{
public:
	friend class Food;
	friend class Simulation;

	Board(QQuickItem* pView);

	QQuickItem* view();
	qreal cellSize() const;
	qreal scaledCellSize() const;
	int rows() const;
	int columns() const;
	qreal height() const;
	qreal scaledHeight() const;
	qreal width() const;
	qreal scaledWidth() const;

private:
	QQuickItem* mView;
	qreal mCellSize; // [m]
	int mRows;
	int mColumns;

	void init();
};


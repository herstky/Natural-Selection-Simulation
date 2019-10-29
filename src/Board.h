#pragma once

#include <QQuickItem>

#include <vector>

#include "View.h"

class Simulation;
class CircleTrainingScenario;

class Board
{
public:
	friend class Food;
	friend class Simulation;
	friend class Scenario;

	Board(QQuickItem& pView);

	QQuickItem& view();
	qreal cellSize() const;
	qreal scaledCellSize() const;
	int rows() const;
	int columns() const;
	qreal height() const;
	qreal heightP() const;
	qreal width() const;
	qreal widthP() const;

	const qreal M_CELL_SIZE; // [m]

private:
	QQuickItem& mView;
	int mRows;
	int mColumns;
	
	void init();
};


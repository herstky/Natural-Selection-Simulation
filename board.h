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
	~Board();

	QQuickItem* view();
	qreal cellSize() const;
	qreal scaledCellSize() const;
	int rows() const;
	int columns() const;
	qreal height() const;
	qreal scaledHeight() const;
	qreal width() const;
	qreal scaledWidth() const;
	std::vector<std::vector<qreal>>* grid();
	std::vector<std::vector<qreal>> mGrid;
	void diffuseParticles(const Simulation& pSimulation);

private:
	QQuickItem* mView;
	qreal mCellSize; // [m]
	int mRows;
	int mColumns;

	void init();
};


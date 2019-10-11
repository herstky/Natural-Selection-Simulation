#pragma once

#include <QQuickItem>

#include <vector>

class Simulation;

class Board
{
	friend class Food;
	friend class Simulation;
public:
	Board(QQuickItem* view);
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
	// each grid element is a qreal representing number of Food particles in moles
	std::vector<std::vector<qreal>> mGrid;
	void diffuseParticles(const Simulation& simulation); // TODO: move this function to its own thread

private:
	QQuickItem* mView;
	qreal mCellSize; // [m]
	int mRows;
	int mColumns;

	void init();
};


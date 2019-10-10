#pragma once

#include <QQuickItem>

#include <vector>

class Simulation;

class Board
{
	friend class Simulation;
public:
	Board(QQuickItem* view);
	~Board();

	QQuickItem* view();
	qreal cellSize();
	qreal scaledCellSize();
	int rows();
	int columns();
	qreal height();
	qreal width();
	std::vector<std::vector<qreal>>* grid();
	// each grid element is a qreal representing number of Food particles in moles
	std::vector<std::vector<qreal>> mGrid;
	void diffuseParticles(const Simulation& simulation);

private:
	QQuickItem* mView;
	qreal mCellSize; // [m]
	int mRows;
	int mColumns;

	void init();
};


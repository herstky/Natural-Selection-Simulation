#pragma once

#include <QQuickItem>

class Board
{
public:
	Board(QQuickItem* view);
	~Board();

	QQuickItem* view;

private:
	qreal cellSize;
	int rows;
	int columns;
};


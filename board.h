#pragma once

#include <QQuickItem>

class Board
{
public:
	Board();
	~Board();

	int height();
	int width();

private:
	qreal cellSize;
	int rows;
	int columns;
};


#pragma once

#include <QQuickItem>

class Board
{
public:
	Board();
	~Board();

private:
	qreal cellSize;
	int rows;
	int columns;
};


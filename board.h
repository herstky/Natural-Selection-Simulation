#pragma once

#include <QQuickItem>

class Board
{
public:
	Board();
	~Board();

private:
	qreal mCellSize;
	int mRows;
	int mColumns;
};


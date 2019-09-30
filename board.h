#pragma once

#include <QQuickPaintedItem>
#include <QPainter>

class Board :
	public QQuickPaintedItem
{
	Q_OBJECT
public:
	Board(QQuickItem* parent = nullptr);
	Board(QQuickItem* parent, qreal cellSize, int rows, int columns);
	Board(const Board& other);
	~Board();

	void paint(QPainter* painter);
private:
	QColor color;
	qreal cellSize;
	int rows;
	int columns;

};


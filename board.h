#pragma once

#include <QQuickPaintedItem>
#include <QPainter>
#include <QQuickItem>

class Board :
	public QQuickPaintedItem
{
	Q_OBJECT
public:
	Board(QQuickItem* parent = nullptr);
	Board(QQuickItem* parent, qreal cellSize, int rows, int columns);
	~Board();

	void paint(QPainter* painter);
private:
	QColor color;
	qreal cellSize;
	int rows;
	int columns;

};


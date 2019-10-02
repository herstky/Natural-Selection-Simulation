#pragma once

#include "entity.h"

class Model
{
public:
	Model();
	~Model();

	enum Shape { ellipse, rectangle, roundedRectangle };
	
	QColor color;
	Shape shape;
	qreal height;
	qreal width;
	qreal x;
	qreal y;

};


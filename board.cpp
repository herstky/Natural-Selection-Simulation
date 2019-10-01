#include "board.h"

#include "constants.h"

#include <iostream>

Board::Board(QQuickItem* view)
	: view(view),
	  cellSize(1),
	  rows(30),
	  columns(60)
{
	view->setHeight(300.0);
	view->setWidth(300.0);
	view->setFlag(QQuickItem::ItemHasContents);
}

Board::~Board() 
{
	std::cout << "Board destructor called" << std::endl;
}


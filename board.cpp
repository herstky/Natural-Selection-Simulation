#include "board.h"

#include "constants.h"

#include <iostream>

Board::Board() 
	: cellSize(1),
	  rows(30),
	  columns(60) {}

Board::~Board() {}

int Board::height()
{
	return SCALE_FACTOR * cellSize * rows;
}

int Board::width()
{
	return SCALE_FACTOR * cellSize * columns;
}

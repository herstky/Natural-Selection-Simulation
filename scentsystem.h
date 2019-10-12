#pragma once

#include <unordered_map>
#include <string>

#include "board.h"

class ScentSystem
{
public:
	ScentSystem(Board* board);
	~ScentSystem();

	void diffuse();

private:
	std::unordered_map<std::string, qreal> mScentMap;
	Board* mBoard;
};


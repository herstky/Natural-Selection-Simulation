#include "scentsystem.h"
#include <string>
#include <iostream>
ScentSystem::ScentSystem(Board* board)
	: mScentMap(std::unordered_map<std::string, qreal>()), mBoard(board) 
{
	mScentMap.emplace("key", 1);
}

ScentSystem::~ScentSystem() {}

void ScentSystem::diffuse()
{
	for (auto it = mScentMap.begin(); it != mScentMap.end(); it++)
	{
		std::cout << it->first << ":" << it->second << '\n';
	}
}
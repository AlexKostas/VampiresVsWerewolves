#include <cassert>
#include <iostream>
#include "WaterCell.h"

using std::cout;

WaterCell::WaterCell(int row, int column, Map* game): GameEntity(row, column, game) {}

void WaterCell::update()
{
}

void WaterCell::print()
{
	cout << "~";
}

bool WaterCell::IsGround()
{
	return false;
}

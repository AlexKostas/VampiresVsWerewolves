#include <iostream>
#include <cassert>
#include "Ground.h"

using std::cout;

Ground::Ground(int row, int column, Map* game) : GameEntity(row, column, game) {}

void Ground::update()
{
}

void Ground::print()
{
	cout << " ";
}

bool Ground::IsGround()
{
	return true;
}

#include <iostream>
#include "Water.h"

using std::cout;

Water::Water(int row, int column) : MapElement(row, column){}

void Water::Print() const
{
	std::cout << "\033[1;44;37m ~ \033[0m";
}

bool Water::CanBeOccupied() const
{
	return false;
}

#include <iostream>
#include "Water.h"

using std::cout;

Water::Water(int row, int column) : MapElement(row, column){}

void Water::Print() const
{
	cout << "~";
}

bool Water::CanBeOccupied() const
{
	return false;
}

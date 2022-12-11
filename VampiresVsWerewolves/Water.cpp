#include <iostream>
#include "Water.h"

using std::cout;

void Water::Print() const
{
	cout << "~";
}

bool Water::CanBeOccupied() const
{
	return false;
}

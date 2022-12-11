#include <iostream>
#include "Water.h"

using std::cout;

void Water::Print() const
{
	if (!isOccupied()) cout << "~";
	else occupant->Print();
}

bool Water::CanBeOccupied() const
{
	return false;
}

#include <iostream>
#include "Tree.h"

using std::cout;

void Tree::Print() const
{
	if (!isOccupied()) cout << "T";
	else occupant->Print();
}

bool Tree::CanBeOccupied() const
{
	return false;
}

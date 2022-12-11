#include <iostream>
#include "Ground.h"
#include "GameEntity.h"

using std::cout;

void Ground::Print() const
{
	if (!isOccupied()) cout << " ";
	else occupant->Print();
}

bool Ground::CanBeOccupied() const
{
	return !isOccupied();
}

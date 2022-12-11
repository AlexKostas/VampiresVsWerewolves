#include <iostream>
#include "Ground.h"
#include "MapElement.h"
#include "GameEntity.h"

using std::cout;

Ground::Ground(int row, int column) : MapElement(row, column){}

void Ground::Print() const
{
	if (HasPotion()) cout << "P";
	else if (!IsOccupied()) cout << " ";
	else occupant->Print();
}

bool Ground::CanBeOccupied() const
{
	return !IsOccupied();
}

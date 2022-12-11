#include <iostream>
#include "Ground.h"
#include "MapElement.h"
#include "GameEntity.h"

using std::cout;

void Ground::Print() const
{
	if (HasPotion()) cout << "P";
	else if (!isOccupied()) cout << " ";
	else occupant->Print();
}

bool Ground::CanBeOccupied() const
{
	return !isOccupied() && !HasPotion();
}

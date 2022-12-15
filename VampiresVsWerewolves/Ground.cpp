#include <iostream>
#include "Ground.h"
#include "MapElement.h"
#include "GameEntity.h"

using std::cout;

Ground::Ground(int row, int column) : MapElement(row, column){}

void Ground::Print() const
{
	// Print everything with a green background using special characters
	if (HasPotion()) cout << "\033[1;42;30m P \033[0m";
	else if (!IsOccupied()) cout << "\033[1;42m   \033[0m";
	else {
		cout << "\033[1;42m ";
		occupant->Print();
		cout << "\033[1;42m \033[0m";
	}
}

bool Ground::CanBeOccupied() const
{
	return !IsOccupied();
}

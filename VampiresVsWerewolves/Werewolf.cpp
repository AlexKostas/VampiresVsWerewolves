#include <cassert>
#include <iostream>
#include "Werewolf.h"
#include "Utils.h"

using std::cout;

Werewolf::Werewolf(int row, int column, Map* game) : GameEntity(row, column, game) {}

void Werewolf::update() {
	//vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	//int legalCellCount = legalCells.size();

	//if (legalCellCount == 0) //TODO: attack
	//	return;

	//int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount);
	//assert(randomIndex >= 0 && randomIndex < legalCellCount);
	//pair<int, int> coords = legalCells[randomIndex];

	//row = coords.first;
	//column = coords.second;
}

void Werewolf::print()
{
	cout << "W";
}

bool Werewolf::IsGround()
{
	return false;
}

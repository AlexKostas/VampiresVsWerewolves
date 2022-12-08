#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
#include "Vampire.h"
#include "Utils.h"

using std::cout;

Vampire::Vampire(int row, int column, Map* game) : GameEntity(row, column, game) {}

void Vampire::update(){
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

void Vampire::print()
{
	cout << "V";
}

bool Vampire::IsGround()
{
	return false;
}

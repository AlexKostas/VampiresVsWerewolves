#include <cassert>
#include <iostream>
#include "Avatar.h"
#include "Game.h"
#include "Utils.h"


using std::cout;

Avatar::Avatar(int row, int column, Map* game) : GameEntity(row, column, game){}

void Avatar::update() {
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

void Avatar::print()
{
	cout << "A";
}

bool Avatar::IsGround()
{
	return false;
}

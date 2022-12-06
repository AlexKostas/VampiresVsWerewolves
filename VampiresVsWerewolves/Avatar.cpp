#include <cassert>
#include "Avatar.h"
#include "Game.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(game != NULL);

	this->row = row;
	this->column = column;
	this->game = game;
}

void Avatar::update() {
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	int legalCellCount = legalCells.size();

	if (legalCellCount == 0) //TODO: attack
		return;

	int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount);
	assert(randomIndex >= 0 && randomIndex < legalCellCount);
	pair<int, int> coords = legalCells[randomIndex];

	row = coords.first;
	column = coords.second;
}

MapCellType Avatar::GetCellType() {
	return MapCellType::avatar;
}
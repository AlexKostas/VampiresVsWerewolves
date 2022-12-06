#include <cassert>
#include <vector>
#include <utility>
#include "Vampire.h"
#include "Utils.h"

Vampire::Vampire(int row, int column, Game* game)
{
	assert(row >= 0);
	assert(column >= 0);

	this->row = row;
	this->column = column;
	this->game = game;
}

void Vampire::update(){
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

MapCellType Vampire::GetCellType() {
	return MapCellType::vampire;
}
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
	vector<pair<int, int>> diagonalCells = game->GetAvailableDiagonalNeighboringCells(row, column);

	// Join the two vectors of possible movement target cells
	vector<pair<int, int>> possibleMovementCells = legalCells;
	possibleMovementCells.insert(possibleMovementCells.end(), diagonalCells.begin(), diagonalCells.end());

	int legalCellCount = possibleMovementCells.size();

	if (legalCellCount == 0) //TODO: attack
		return;

	int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount+1);
	assert(randomIndex >= 0 && randomIndex <= legalCellCount);

	if (randomIndex == legalCellCount) return;

	pair<int, int> coords = possibleMovementCells[randomIndex];

	row = coords.first;
	column = coords.second;
}

MapCellType Vampire::GetCellType() {
	return MapCellType::vampire;
}
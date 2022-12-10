#include <cassert>
#include <vector>
#include <utility>
#include "Vampire.h"
#include "Werewolf.h"
#include "Utils.h"

Vampire::Vampire(int row, int column, Game* game) : Enemy(row, column, game){}

MapCellType Vampire::GetCellType() {
	return MapCellType::vampire;
}

vector<Enemy*> Vampire::getEnemies()
{
	return game->GetNeighboringWerewolves(row, column);
}

vector<Enemy*> Vampire::getAllies()
{
	return game->GetNeighboringVampires(row, column);
}

vector<pair<int, int>> Vampire::getPossibleMovementCells()
{
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	vector<pair<int, int>> diagonalCells = game->GetAvailableDiagonalNeighboringCells(row, column);

	// Join the two vectors of possible movement target cells
	vector<pair<int, int>> possibleMovementCells = legalCells;
	possibleMovementCells.insert(possibleMovementCells.end(), diagonalCells.begin(), diagonalCells.end());

	return possibleMovementCells;
}

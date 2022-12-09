#include <cassert>
#include "Werewolf.h"
#include "Utils.h"

Werewolf::Werewolf(int row, int column, Game* game) : GameEntity(row, column, game) {}

void Werewolf::update() {
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	int legalCellCount = legalCells.size();

	if (legalCellCount == 0) //TODO: attack
		return;

	int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount+1);
	assert(randomIndex >= 0 && randomIndex <= legalCellCount);

	if (randomIndex == legalCellCount) return;

	pair<int, int> coords = legalCells[randomIndex];

	row = coords.first;
	column = coords.second;
}

MapCellType Werewolf::GetCellType() {
	return MapCellType::werewolf;
}
#include <cassert>
#include <vector>
#include <utility>
#include "Vampire.h"
#include "Werewolf.h"
#include "Utils.h"

Vampire::Vampire(int row, int column, Game* game) : Enemy(row, column, game){}

void Vampire::update(){
	vector<Vampire*> allies = game->GetNeighboringVampires(row, column);
	vector<Werewolf*> enemies = game->GetNeighboringWerewolves(row, column);

	// Try to heal ally
	if (allies.size() > 0 && healthKits > 0) {
		int allyIndex = Utils::GetRandomNumberInRange(0, allies.size());
		if (allies[allyIndex]->TryToApplyHealthkit()) {
			healthKits--;
			return;
		}
	}
	else if (enemies.size() > 0) { // Next, try to attack nearby enemy
		int enemyIndex = Utils::GetRandomNumberInRange(0, enemies.size());
		Werewolf* enemyToAttack = enemies[enemyIndex];

		if (enemyToAttack->CanAttack(attack)) {
			enemyToAttack->DoDamage(attack);
			return;
		}

	}

	// Finally, try to move
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	vector<pair<int, int>> diagonalCells = game->GetAvailableDiagonalNeighboringCells(row, column);

	// Join the two vectors of possible movement target cells
	vector<pair<int, int>> possibleMovementCells = legalCells;
	possibleMovementCells.insert(possibleMovementCells.end(), diagonalCells.begin(), diagonalCells.end());

	int legalCellCount = possibleMovementCells.size();

	if (legalCellCount == 0)
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
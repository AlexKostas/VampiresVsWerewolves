#include <cassert>
#include "Werewolf.h"
#include "Vampire.h"
#include "Utils.h"

Werewolf::Werewolf(int row, int column, Game* game) : Enemy(row, column, game) {}

void Werewolf::update() {
	vector<Vampire*> enemies = game->GetNeighboringVampires(row, column);
	vector<Werewolf*> allies = game->GetNeighboringWerewolves(row, column);

	if (allies.size() > 0 && healthKits > 0) {
		int allyIndex = Utils::GetRandomNumberInRange(0, allies.size());
		if (allies[allyIndex]->TryToApplyHealthkit()) {
			healthKits--;
			return;
		}
	}
	else if (enemies.size() > 0) {
		int enemyIndex = Utils::GetRandomNumberInRange(0, enemies.size());
		Vampire* enemyToAttack = enemies[enemyIndex];

		if (enemyToAttack->CanAttack(attack)) {
			DoDamage(attack);
			return;
		}

	}

	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);
	int legalCellCount = legalCells.size();

	if (legalCellCount == 0)
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
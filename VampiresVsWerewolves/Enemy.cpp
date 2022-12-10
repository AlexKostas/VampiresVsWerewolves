#include <iostream>
#include <cassert>
#include "Game.h"
#include "Enemy.h"
#include "Utils.h"

using std::cout;
using std::endl;

Enemy::Enemy(int row, int col, Game* game) : GameEntity(row, col, game)
{
	this->healthKits = Utils::GetRandomNumberInRange(0, maxHealthKits + 1);
	this->health = startingHealth;

	assert(maxDefense < maxAttack);
	this->attack = Utils::GetRandomNumberInRange(maxDefense + 1, maxAttack + 1);
	this->defence = Utils::GetRandomNumberInRange(1, maxDefense + 1);
}

void Enemy::update()
{
	vector<Enemy*> allies = getAllies();
	vector<Enemy*> enemies = getEnemies();

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
		Enemy* enemyToAttack = enemies[enemyIndex];

		if (enemyToAttack->CanAttack(attack)) {
			enemyToAttack->DoDamage(attack);
			return;
		}

	}

	// Finally, try to move
	vector<pair<int, int>> possibleMovementCells = getPossibleMovementCells();
	int legalCellCount = possibleMovementCells.size();

	if (legalCellCount == 0)
		return;

	int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount + 1);
	assert(randomIndex >= 0 && randomIndex <= legalCellCount);

	if (randomIndex == legalCellCount) return;

	pair<int, int> coords = possibleMovementCells[randomIndex];

	row = coords.first;
	column = coords.second;
}

/// <summary>
/// Tries to apply a heath kit and returns true if it
/// succeeds. Otherwise return false.
/// </summary>
bool Enemy::TryToApplyHealthkit()
{
	if (health >= startingHealth) return false;

	health++;
	return true;
}

void Enemy::DoDamage(int myAttack)
{
	int damage = myAttack - defence;
	if (damage <= 0) return;

	health -= damage;
	if (health <= 0)
		die();
}

void Enemy::DisplayHealth() const
{
	cout << health << endl;
}

bool Enemy::CanAttack(int myAttack) const
{
	int chance = Utils::GetRandomNumberInRange(1, 101);
	if (chance > 85) return true;

	return myAttack > attack;
}

void Enemy::die()
{
	game->OnEntityDied(this);
}

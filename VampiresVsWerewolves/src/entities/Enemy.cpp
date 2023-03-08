#include <iostream>
#include <cassert>
#include "Game.h"
#include "MapElement.h"
#include "Enemy.h"
#include "Utils.h"

using std::cout;
using std::endl;

Enemy::Enemy(int row, int col, Game* game, MapElement* cell) : GameEntity(row, col, game, cell)
{
	this->healthKits = Utils::GetRandomNumberInRange(0, maxHealthKits + 1);
	this->health = startingHealth;

	assert(maxDefense < maxAttack);
	this->attack = Utils::GetRandomNumberInRange(maxDefense + 1, maxAttack + 1);
	this->defence = Utils::GetRandomNumberInRange(1, maxDefense + 1);
}

void Enemy::Update()
{
	// During its turn, the entity will first try to heal an ally.
	// If that isn't possible it will try to attack. If that fails
	// to, the enemy will move to a neighboring cell.

	if (tryToHealAlly()) return;
	if (tryToAttack()) return;
	if (tryToMove()) return;

	// We should never reach the point where no action was taken
	// Please note that not moving at all is an action itself.
	assert(false);
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

void Enemy::RefillHealth()
{
	health = startingHealth;
}

bool Enemy::CanAttack(int myAttack) const
{
	int chance = Utils::GetRandomNumberInRange(1, 101);
	if (chance > 85) return true;

	return myAttack > attack;
}

/// <summary>
/// Tries to heal a teammate. Returns true if it succeeds,
/// otherwise returns false.
/// </summary>
bool Enemy::tryToHealAlly()
{
	vector<Enemy*> allies = getAllies();

	if (allies.size() <= 0 || healthKits <= 0) return false;

	int allyIndex = Utils::GetRandomNumberInRange(0, allies.size());
	if (allies[allyIndex]->TryToApplyHealthkit()) {
		healthKits--;
		return true;
	}
	
	return false;
}

/// <summary>
/// Tries to attack an enemy. Returns true if it succeeds,
/// otherwise returns false.
/// </summary>
bool Enemy::tryToAttack()
{
	vector<Enemy*> enemies = getEnemies();

	if (enemies.size() <= 0) return false;
 
	int enemyIndex = Utils::GetRandomNumberInRange(0, enemies.size());
	Enemy* enemyToAttack = enemies[enemyIndex];

	if (enemyToAttack->CanAttack(attack)) {
		enemyToAttack->DoDamage(attack);
		return true;
	}

	return false;
}

/// <summary>
/// Tries to move to a neighboring cell. Returns true if it succeeds,
/// otherwise returns false.
/// </summary>
bool Enemy::tryToMove()
{
	vector<MapElement*> possibleMovementCells = getPossibleMovementCells();
	int legalCellCount = possibleMovementCells.size();

	if (legalCellCount == 0)
		return false;

	// The upper bound for the index is one higher than the number of cells
	// we can move to, so as to provide the option for the entity to not 
	// move at all.
	int randomIndex = Utils::GetRandomNumberInRange(0, legalCellCount + 1);
	assert(randomIndex >= 0 && randomIndex <= legalCellCount);

	// The action to take is to do nothing, so we return true.
	if (randomIndex == legalCellCount) return true;

	// Removing the enemy from the current cell...
	cell->Clear();

	//... and assigning them to their destination one.
	MapElement* targetMapCell = possibleMovementCells[randomIndex];

	row = targetMapCell->GetRow();
	column = targetMapCell->GetColumn();

	targetMapCell->SetOccupant(this);
	cell = targetMapCell;

	return true;
}

void Enemy::die()
{
	cell->Clear();
	game->OnEntityDied(this);
}


void Enemy::DisplayInfo() const
{
	if (health <= 2) {
		cout << getName()<<": Health = \033[1;31m" << health << "\033[0m/" << startingHealth << endl;
		return;
	}
	cout << getName() << ": Health = " << health << "/" << startingHealth << endl;
}
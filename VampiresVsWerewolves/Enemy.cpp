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

#include <cassert>
#include <iostream>
#include "GameEntity.h"
#include "Utils.h"

using std::cout;
using std::endl;

GameEntity::GameEntity(int row, int column, Game* game)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(game != NULL);

	this->row = row;
	this->column = column;
	this->game = game;

	this->healthKits = Utils::GetRandomNumberInRange(0, maxHealthKits + 1);
	this->health = startingHealth;
	assert(maxDefense < maxAttack);
	this->attack = Utils::GetRandomNumberInRange(maxDefense+1, maxAttack + 1);
	this->defence = Utils::GetRandomNumberInRange(1, maxDefense + 1);
}

/// <summary>
/// Tries to apply a heath kit and returns true if it
/// succeeds. Otherwise return false.
/// </summary>
bool GameEntity::TryToApplyHealthkit()
{
	if (health >= startingHealth) return false;

	health++;
	return true;
}

void GameEntity::DoDamage(int myAttack)
{
	int damage = myAttack - defence;
	if (damage <= 0) return;

	health -= damage;
	if (health <= 0)
		die();
}

void GameEntity::DisplayHealth()
{
	cout << health << endl;
}

int GameEntity::getRow() const
{
    return row;
}

int GameEntity::getColumn() const
{
    return column;
}

bool GameEntity::CanAttack(int myAttack) const
{
	int chance = Utils::GetRandomNumberInRange(1, 101);
	if (chance > 85) return true;

	return myAttack > attack;
}

void GameEntity::die()
{
	game->OnEntityDied(this);
}
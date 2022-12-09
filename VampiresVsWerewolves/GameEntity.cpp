#include <cassert>
#include "GameEntity.h"
#include "Utils.h"

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
	this->attack = Utils::GetRandomNumberInRange(1, maxAttack + 1);
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
	assert(damage >= 0);

	health -= damage;
	if (health <= 0)
		die();
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
	return myAttack > defence;
}

void GameEntity::die()
{
}
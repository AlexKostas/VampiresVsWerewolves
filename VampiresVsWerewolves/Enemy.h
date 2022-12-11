#pragma once
#include "Enums.h"
#include "GameEntity.h"

class Game;

class Enemy : public GameEntity {
public:
	Enemy(int row, int col, Game* game);
	virtual void update();

	bool TryToApplyHealthkit();
	bool CanAttack(int myAttack) const;
	void DoDamage(int myAttack);
	void DisplayHealth() const;
protected:
	const int maxHealthKits = 2;
	const int startingHealth = 5;
	const int maxAttack = 3; // NEEDS TO BE HIGHER THAN MAX DEFENSE
	const int maxDefense = 2;

	int health, attack, defence, healthKits;
	void die();
	virtual vector<Enemy*> getEnemies() = 0;
	virtual vector<Enemy*> getAllies() = 0;
	virtual vector<MapElement*> getPossibleMovementCells() = 0;
};

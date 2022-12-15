#pragma once
#include "Enums.h"
#include "GameEntity.h"

class Game;

class Enemy : public GameEntity {
public:
	Enemy(int row, int col, Game* game, MapElement* cell);

	virtual void update();
	virtual Team GetTeam() const = 0;
	virtual void DisplayInfo() const;

	bool TryToApplyHealthkit();//returns true if we can managed to apply health kit
	bool CanAttack(int myAttack) const;
	void DoDamage(int myAttack);
	void RefillHealth();
protected:
	const int maxHealthKits = 2;
	const int startingHealth = 5;
	const int maxAttack = 3; // NEEDS TO BE HIGHER THAN MAX DEFENSE
	const int maxDefense = 2;

	int health, attack, defence, healthKits;
	void die();
	virtual string getName() const =0;
	virtual vector<Enemy*> getEnemies() const = 0;
	virtual vector<Enemy*> getAllies() const = 0;
	virtual vector<MapElement*> getPossibleMovementCells() const = 0;
};

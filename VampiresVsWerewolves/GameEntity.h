#pragma once
#include "Game.h"
#include "Enums.h"

class Game;

class GameEntity {
public:
	GameEntity(int row, int column, Game* game);
	virtual void update()=0;
	virtual MapCellType GetCellType() = 0;
	bool TryToApplyHealthkit();
	void DoDamage(int myAttack);
	void DisplayHealth();

	int getRow() const;
	int getColumn() const;
	bool CanAttack(int myAttack) const;
	
protected:
	const int maxHealthKits = 2;
	const int startingHealth = 5;
	const int maxAttack = 3; // NEEDS TO BE HIGHER THAN MAX DEFENSE
	const int maxDefense = 2;
	int row, column;
	int health, attack, defence, healthKits;
	Game* game;

	void die();
};
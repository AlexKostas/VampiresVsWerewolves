#pragma once
#include "GameEntity.h"
#include "Game.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();
	void GoUp();
	void GoDown();
	void GoRight();
	void GoLeft();
	int GetAmountOfPotions();
private:
	int potions=1;
	void gotPotion();
};
#pragma once
#include "GameEntity.h"
#include "Game.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Game* game, bool supportsWerewolves);
	virtual void update();
	virtual void Print();
	virtual MapCellType GetCellType();
	void GoUp();
	void GoDown();
	void GoRight();
	void GoLeft();
	int GetAmountOfPotions();
	bool SupportsWerewolves();
private:
	int potions=1;
	const bool supportsWerewolves;
	void gotPotion();
};
#pragma once
#include "GameEntity.h"
#include "Game.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Game* game, MapElement* cell, Team supportedTeam);
	virtual void update();
	virtual void Print() const;
	void DisplayInfo() const;
	virtual Team GetTeam() const;

	void GoUp();
	void GoDown();
	void GoRight();
	void GoLeft();
	void UsePotion();
	int GetAmountOfPotions();
	bool SupportsWerewolves();
private:
	int potions=1;
	const Team supportedTeam;
	void gotPotion();
	bool canUsePotion() const;
};
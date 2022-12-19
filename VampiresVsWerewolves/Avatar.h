#pragma once
#include "GameEntity.h"
#include "Game.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Game* game, MapElement* cell, Team supportedTeam);

	virtual void Update();

	virtual void Print() const;
	void DisplayInfo() const;

	virtual Team GetTeam() const;

	void GoUp();
	void GoDown();
	void GoRight();
	void GoLeft();

	void UsePotion();
	int GetAmountOfPotions();

	void PrintSupportedTeam();
private:
	int potions=1;
	const Team supportedTeam;

	void moveTo(int row, int col);
	void gotPotion();
	bool canUsePotion() const;
};
#pragma once
#include "Game.h"
#include "Enums.h"

class Game;

class GameEntity {
public:
	GameEntity(int row, int column, Game* game);
	virtual void update()=0;
	virtual MapCellType GetCellType() = 0;

	int getRow() const;
	int getColumn() const;
	
protected:
	int row, column;
	int health, attack, defence;
	Game* game;
};
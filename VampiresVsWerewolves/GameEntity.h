#pragma once
#include "Game.h"
#include "Enums.h"

class Game;
class Enemy;

class GameEntity {
public:
	GameEntity(int row, int column, Game* game, MapElement* cell);

	virtual void Update() = 0;

	virtual void Print() const = 0;
	virtual void DisplayInfo() const = 0;

	virtual Team GetTeam() const = 0;
	
	int getRow() const;
	int getColumn() const;	

protected:
	int row, column;
	Game* game;
	MapElement* cell;
};
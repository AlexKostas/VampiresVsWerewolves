#pragma once

class Map;

class GameEntity {
public:
	GameEntity(int row, int col, Map* map);
	virtual void update() = 0;
	virtual void print() = 0;
	virtual bool IsGround() = 0;

	int getRow() const;
	int getColumn() const;
	
protected:
	int row, column;
	int health, attack, defence;
	Map* game;
};
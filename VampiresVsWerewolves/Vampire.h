#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Vampire : public Enemy {
public:
	Vampire(int row, int column, Game* game);
	virtual MapCellType GetCellType();
	virtual void Print();

private:
	virtual vector<Enemy*> getEnemies();
	virtual vector<Enemy*> getAllies();
	virtual vector<pair<int, int>> getPossibleMovementCells();
};
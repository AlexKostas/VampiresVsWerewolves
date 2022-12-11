#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Werewolf : public Enemy {
public:
	Werewolf( int row, int column, Game* game);
	virtual void Print();

private:
	virtual vector<Enemy*> getEnemies();
	virtual vector<Enemy*> getAllies();
	virtual vector<pair<int, int>> getPossibleMovementCells();
};
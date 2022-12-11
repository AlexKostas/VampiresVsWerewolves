#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Vampire : public Enemy {
public:
	Vampire(int row, int column, Game* game, MapElement* cell);
	virtual void Print();
	virtual Team GetTeam();

private:
	virtual vector<Enemy*> getEnemies();
	virtual vector<Enemy*> getAllies();
	virtual vector<MapElement*> getPossibleMovementCells();
};
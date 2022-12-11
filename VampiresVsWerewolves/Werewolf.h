#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Werewolf : public Enemy {
public:
	Werewolf( int row, int column, Game* game, MapElement* cell);
	virtual void Print();
	virtual void DisplayInfo() const;
	virtual Team GetTeam();

private:
	virtual vector<Enemy*> getEnemies();
	virtual vector<Enemy*> getAllies();
	virtual vector<MapElement*> getPossibleMovementCells();
};
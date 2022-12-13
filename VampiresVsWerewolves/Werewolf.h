#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Werewolf : public Enemy {
public:
	Werewolf( int row, int column, Game* game, MapElement* cell);
	virtual void Print() const;
	virtual void DisplayInfo() const;
	virtual Team GetTeam() const;

private:
	virtual vector<Enemy*> getEnemies() const;
	virtual vector<Enemy*> getAllies() const;
	virtual vector<MapElement*> getPossibleMovementCells() const;
};
#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Werewolf : public Enemy {
public:
	Werewolf( int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();

private:
};
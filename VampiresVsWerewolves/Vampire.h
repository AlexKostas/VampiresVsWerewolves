#pragma once
#include "GameEntity.h"
#include "Enemy.h"

class Vampire : public Enemy {
public:
	Vampire(int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();

private:
};
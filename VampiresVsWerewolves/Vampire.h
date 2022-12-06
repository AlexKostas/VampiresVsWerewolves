#pragma once
#include "GameEntity.h"

class Vampire : public GameEntity {
public:
	Vampire(int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();

private:
};
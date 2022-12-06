#pragma once
#include "GameEntity.h"

class Vampire : public GameEntity {
public:
	Vampire(int row, int column);
	virtual void update();
	virtual MapCellType GetCellType();

private:
};
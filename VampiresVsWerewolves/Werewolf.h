#pragma once
#include "GameEntity.h"

class Werewolf : public GameEntity {
public:
	Werewolf( int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();

private:
};
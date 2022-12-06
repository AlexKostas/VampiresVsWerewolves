#pragma once
#include "GameEntity.h"
#include "Game.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Game* game);
	virtual void update();
	virtual MapCellType GetCellType();

private:
	//TODO POTION
};
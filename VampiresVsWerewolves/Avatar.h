#pragma once
#include "GameEntity.h"

class Avatar : public GameEntity {
public:
	Avatar( int row,  int column);
	virtual void update();
	virtual MapCellType GetCellType();

private:
	//TODO POTION
};
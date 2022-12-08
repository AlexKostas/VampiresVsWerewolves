#pragma once
#include "GameEntity.h"

class Ground : public GameEntity {
public:
	Ground(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();
};
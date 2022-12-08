#pragma once
#include "GameEntity.h"

class Vampire : public GameEntity {
public:
	Vampire(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();
};
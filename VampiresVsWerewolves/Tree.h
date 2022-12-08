#pragma once
#include "GameEntity.h"

class Tree : public GameEntity {
public:
	Tree(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();
};
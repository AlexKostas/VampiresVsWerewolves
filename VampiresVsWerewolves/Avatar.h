#pragma once
#include "GameEntity.h"

class Avatar : public GameEntity {
public:
	Avatar(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();

private:
	//TODO POTION
};
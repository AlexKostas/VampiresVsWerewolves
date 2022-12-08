#pragma once
#include "GameEntity.h"

class Werewolf : public GameEntity {
public:
	Werewolf(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();
private:
};
#pragma once
#include "GameEntity.h"


class Werewolf : public GameEntity {
public:
	Werewolf(unsigned int row, unsigned int column);
	virtual void update();


private:
};



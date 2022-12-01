#pragma once
#include "GameEntity.h"


class Vampire : public GameEntity {
public:
	Vampire(unsigned int row, unsigned int column);
	virtual void update();


private:
};

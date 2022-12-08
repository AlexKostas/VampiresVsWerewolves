#pragma once
#include "GameEntity.h"


class WaterCell : public GameEntity {
public:
	WaterCell(int row, int column, Map* game);
	virtual void update();
	virtual void print();
	virtual bool IsGround();
};
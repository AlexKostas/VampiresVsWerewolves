#include <cassert>
#include "GameEntity.h"

GameEntity::GameEntity(int row, int col, Map* map)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(map != NULL);

	this->row = row;
	this->column = column;
	this->game = map;
}

int GameEntity::getRow() const
{
    return row;
}

int GameEntity::getColumn() const
{
    return column;
}
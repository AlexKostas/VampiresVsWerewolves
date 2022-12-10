#include <cassert>
#include "GameEntity.h"
#include "Utils.h"

GameEntity::GameEntity(int row, int column, Game* game)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(game != NULL);

	this->row = row;
	this->column = column;
	this->game = game;
}

int GameEntity::getRow() const
{
	return row;
}

int GameEntity::getColumn() const
{
	return column;
}
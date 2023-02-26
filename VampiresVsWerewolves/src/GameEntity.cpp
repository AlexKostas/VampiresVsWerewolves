#include <cassert>
#include "GameEntity.h"
#include "MapElement.h"
#include "Utils.h"

GameEntity::GameEntity(int row, int column, Game* game, MapElement* cell)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(game != nullptr);
	assert(cell != nullptr);

	this->row = row;
	this->column = column;
	this->game = game;
	this->cell = cell;
}

int GameEntity::getRow() const
{
	return row;
}

int GameEntity::getColumn() const
{
	return column;
}
#include <cassert>
#include "Werewolf.h"

Werewolf::Werewolf(int row, int column)
{
	//TODO: Maybe move this to parent's constructor
	assert(row >= 0);
	assert(column >= 0);

	this->row = row;
	this->column = column;
}

void Werewolf::update() {

}

MapCellType Werewolf::GetCellType() {
	return MapCellType::werewolf;
}
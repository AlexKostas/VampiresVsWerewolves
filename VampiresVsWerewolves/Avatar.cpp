#include <cassert>
#include "Avatar.h"

Avatar::Avatar(int row,  int column)
{
	assert(row >= 0);
	assert(column >= 0);

	this->row = row;
	this->column = column;
}

void Avatar::update() {

}

MapCellType Avatar::GetCellType() {
	return MapCellType::avatar;
}
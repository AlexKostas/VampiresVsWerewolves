#include <cassert>
#include "Vampire.h"

Vampire::Vampire(int row, int column)
{
	assert(row >= 0);
	assert(column >= 0);

	this->row = row;
	this->column = column;
}

void Vampire::update(){

}

MapCellType Vampire::GetCellType() {
	return MapCellType::vampire;
}
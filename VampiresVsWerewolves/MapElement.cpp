#include <cassert>
#include "MapElement.h"

MapElement::MapElement(int row, int column)
{
	this->row = row;
	this->column = column;
	this->occupant = nullptrptr;
}

void MapElement::Clear()
{
	occupant = nullptrptr;
}

void MapElement::SetOccupant(GameEntity* occupant)
{
	assert(occupant != nullptrptr);
	assert(CanBeOccupied());
	this->occupant = occupant;
}

GameEntity* MapElement::GetOccupant() const
{
	return occupant;
}

void MapElement::PlacePotion()
{
	assert(CanBeOccupied());
	hasPotion = true;
}

void MapElement::RemovePotion()
{
	assert(HasPotion());
	hasPotion = false;
}

bool MapElement::HasPotion() const
{
	return hasPotion;
}

int MapElement::GetRow() const
{
	return row;
}

int MapElement::GetColumn() const
{
	return column;
}

bool MapElement::IsOccupied() const
{
	return occupant != nullptrptr;
}

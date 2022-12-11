#include <cassert>
#include "MapElement.h"

MapElement::MapElement(int row, int column)
{
	this->row = row;
	this->column = column;
}

void MapElement::Clear()
{
	occupant = nullptr;
	hasPotion = false;
}

void MapElement::SetOccupant(GameEntity* occupant)
{
	assert(occupant != nullptr);
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
	assert(!hasPotion);
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

bool MapElement::isOccupied() const
{
	return occupant != nullptr;
}

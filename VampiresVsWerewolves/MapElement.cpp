#include <cassert>
#include "MapElement.h"

void MapElement::Clear()
{
	occupant = nullptr;
}

void MapElement::SetOccupant(GameEntity* occupant)
{
	assert(occupant != nullptr);
	this->occupant = occupant;
}

GameEntity* MapElement::GetOccupant() const
{
	return occupant;
}

bool MapElement::isOccupied() const
{
	return occupant != nullptr;
}

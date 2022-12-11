#include <cassert>
#include "MapElement.h"

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

bool MapElement::isOccupied() const
{
	return occupant != nullptr;
}

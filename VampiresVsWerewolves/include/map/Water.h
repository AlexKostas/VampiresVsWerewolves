#pragma once
#include "MapElement.h"

class Water : public MapElement {
public:
	Water(int row, int column);

	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
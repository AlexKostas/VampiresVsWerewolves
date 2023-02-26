#pragma once
#include "MapElement.h"

class Ground : public MapElement {
public:
	Ground(int row, int column);

	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
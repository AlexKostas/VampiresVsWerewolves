#pragma once
#include "MapElement.h"

class Water : public MapElement {
public:
	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
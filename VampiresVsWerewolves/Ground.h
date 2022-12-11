#pragma once
#include "MapElement.h"

class Ground : public MapElement {
public:
	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
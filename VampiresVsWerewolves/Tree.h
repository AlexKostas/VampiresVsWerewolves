#pragma once
#include "MapElement.h"

class Tree : public MapElement {
public:
	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
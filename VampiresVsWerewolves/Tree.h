#pragma once
#include "MapElement.h"

class Tree : public MapElement {
public:
	Tree(int row, int column);

	virtual void Print() const;
	virtual bool CanBeOccupied() const;
};
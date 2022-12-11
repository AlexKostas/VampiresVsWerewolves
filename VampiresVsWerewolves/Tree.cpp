#include <iostream>
#include "Tree.h"

using std::cout;

Tree::Tree(int row, int column): MapElement(row, column){}

void Tree::Print() const
{
	cout << "T";
}

bool Tree::CanBeOccupied() const
{
	return false;
}

#include <iostream>
#include "Tree.h"

using std::cout;

Tree::Tree(int row, int column): MapElement(row, column){}

void Tree::Print() const
{
	std::cout << "\033[1;30;43m T \033[0m";
}

bool Tree::CanBeOccupied() const
{
	return false;
}

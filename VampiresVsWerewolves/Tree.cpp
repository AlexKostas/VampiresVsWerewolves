#include "Tree.h"
#include <cassert>
#include <iostream>

using std::cout;


Tree::Tree(int row, int column, Map* game) : GameEntity(row, column, game) {}

void Tree::update()
{

}

void Tree::print()
{
	cout << "T";
}

bool Tree::IsGround()
{
	return false;
}


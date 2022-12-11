#include <iostream>
#include <cassert>
#include "Werewolf.h"
#include "Vampire.h"
#include "Utils.h"

Werewolf::Werewolf(int row, int column, Game* game) : Enemy(row, column, game) {}

void Werewolf::Print()
{
	std::cout << "W";
}

vector<Enemy*> Werewolf::getEnemies()
{
	return game->GetNeighboringVampires(row, column);
}

vector<Enemy*> Werewolf::getAllies()
{
	return game->GetNeighboringWerewolves(row, column);
}

vector<pair<int, int>> Werewolf::getPossibleMovementCells()
{
	return game->GetAvailableNeighboringCells(row, column);
}

#include <iostream>
#include <cassert>
#include "MapElement.h"
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

vector<MapElement*> Werewolf::getPossibleMovementCells()
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<MapElement*> legalNeighbors;

	for (MapElement* neighbor : neighbors)
		if (neighbor->CanBeOccupied()) 
			legalNeighbors.push_back(neighbor);

	return legalNeighbors;
}

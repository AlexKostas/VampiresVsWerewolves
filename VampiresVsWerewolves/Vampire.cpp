#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include "MapElement.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Utils.h"

Vampire::Vampire(int row, int column, Game* game) : Enemy(row, column, game){}

void Vampire::Print()
{
	std::cout << "V";
}

vector<Enemy*> Vampire::getEnemies()
{
	return game->GetNeighboringWerewolves(row, column);
}

vector<Enemy*> Vampire::getAllies()
{
	return game->GetNeighboringVampires(row, column);
}

vector<MapElement*> Vampire::getPossibleMovementCells()
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<MapElement*> diagonalNeighbors = game->GetNeighboringDiagonalCells(row, column);

	// Join the two vectors of possible movement target cells
	vector<MapElement*> combinedNeighbors = neighbors;
	combinedNeighbors.insert(combinedNeighbors.end(), diagonalNeighbors.begin(), diagonalNeighbors.end());

	vector<MapElement*> legalNeighbors;

	for (MapElement* neighbor : neighbors)
		if (neighbor->CanBeOccupied())
			legalNeighbors.push_back(neighbor);

	return legalNeighbors;
}

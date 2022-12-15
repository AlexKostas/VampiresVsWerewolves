#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include "MapElement.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Utils.h"

Vampire::Vampire(int row, int column, Game* game, MapElement* cell) : Enemy(row, column, game, cell){}

void Vampire::Print() const
{
	std::cout << "V";
}

void Vampire::DisplayInfo() const
{
	if (health <= 2) {
		cout << "Vampire: Health = \033[1;31m" << health << "\033[0m/" << startingHealth << endl;
		return;
	}
	cout << "Vampire: Health = " << health << "/" << startingHealth << endl;
}

Team Vampire::GetTeam() const
{
	return Vampires;
}

vector<Enemy*> Vampire::getEnemies() const
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<MapElement*> diagonalNeighbors = game->GetNeighboringDiagonalCells(row, column);
	vector<Enemy*> enemies;

	for (MapElement* neighbor : neighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Werewolves)
			enemies.push_back((Enemy*)neighbor->GetOccupant());
	}

	for (MapElement* neighbor : diagonalNeighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Werewolves)
			enemies.push_back((Enemy*)neighbor->GetOccupant());
	}

	return enemies;
}

vector<Enemy*> Vampire::getAllies() const
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<MapElement*> diagonalNeighbors = game->GetNeighboringDiagonalCells(row, column);
	vector<Enemy*> allies;

	for (MapElement* neighbor : neighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Vampires)
			allies.push_back((Enemy*)neighbor->GetOccupant());
	}

	for (MapElement* neighbor : diagonalNeighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Werewolves)
			allies.push_back((Enemy*)neighbor->GetOccupant());
	}

	return allies;
}

vector<MapElement*> Vampire::getPossibleMovementCells() const
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

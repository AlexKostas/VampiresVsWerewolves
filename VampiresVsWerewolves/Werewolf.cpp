#include <iostream>
#include <cassert>
#include "MapElement.h"
#include "Werewolf.h"
#include "Vampire.h"
#include "Utils.h"

Werewolf::Werewolf(int row, int column, Game* game, MapElement* cell) : Enemy(row, column, game, cell) {}

void Werewolf::Print()
{
	std::cout << "W";
}

void Werewolf::DisplayInfo() const
{
	cout << "Werewolf: Health = " << health << endl;
}

Team Werewolf::GetTeam()
{
	return Werewolves;
}

vector<Enemy*> Werewolf::getEnemies()
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<Enemy*> enemies;

	for (MapElement* neighbor : neighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Vampires)
			enemies.push_back((Enemy*)neighbor->GetOccupant());
	}

	return enemies;
}

vector<Enemy*> Werewolf::getAllies()
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<Enemy*> allies;

	for (MapElement* neighbor : neighbors) {
		if (!neighbor->IsOccupied()) continue;

		if (neighbor->GetOccupant()->GetTeam() == Werewolves)
			allies.push_back((Enemy*)neighbor->GetOccupant());
	}

	return allies;
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

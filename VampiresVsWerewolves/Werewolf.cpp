#include <iostream>
#include <cassert>
#include "MapElement.h"
#include "Werewolf.h"
#include "Vampire.h"
#include "Utils.h"

Werewolf::Werewolf(int row, int column, Game* game, MapElement* cell) : Enemy(row, column, game, cell) {}

void Werewolf::Print() const
{
	std::cout << "W";
}

Team Werewolf::GetTeam() const
{
	return Werewolves;
}

string Werewolf::getName() const
{
	return "Werewolf";
}

vector<Enemy*> Werewolf::getEnemies() const
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

vector<Enemy*> Werewolf::getAllies() const
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

vector<MapElement*> Werewolf::getPossibleMovementCells() const
{
	vector<MapElement*> neighbors = game->GetNeighboringCells(row, column);
	vector<MapElement*> legalNeighbors;

	for (MapElement* neighbor : neighbors)
		if (neighbor->CanBeOccupied() && neighbor->HasPotion()==false) 
			legalNeighbors.push_back(neighbor);

	return legalNeighbors;
}

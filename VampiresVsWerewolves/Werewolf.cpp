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

void Werewolf::DisplayInfo() const
{

	if (health <= 2) {
		cout << "Werewolf: Health = \033[1;31m" << health << "\033[0m/" << startingHealth << endl;
		return;
	}
	cout << "Werewolf: Health = " << health << "/" << startingHealth << endl;
}

Team Werewolf::GetTeam() const
{
	return Werewolves;
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
		if (neighbor->CanBeOccupied()) 
			legalNeighbors.push_back(neighbor);

	return legalNeighbors;
}

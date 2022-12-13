#include <iostream>
#include <cassert>
#include "Avatar.h"
#include "Enemy.h"
#include "Game.h"
#include "MapElement.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game, MapElement* cell, Team _supportedTeam) : GameEntity(row, column, game, cell), 
	supportedTeam(_supportedTeam){}

void Avatar::update() {}

void Avatar::Print() const
{
	std::cout << "\033[1;31mA\033[0m";
}

void Avatar::DisplayInfo() const{}

Team Avatar::GetTeam() const
{
	return Neutral;
}

void Avatar::GoDown()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if(row+1 == cell->GetRow() && column == cell->GetColumn() && cell->CanBeOccupied()) {
			this->cell->Clear();
			row++;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			this->cell = cell;
			break;
		}
	}		
}

void Avatar::GoUp()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row - 1 == cell->GetRow() && column == cell->GetColumn() && cell->CanBeOccupied()) {
			this->cell->Clear();
			row--;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			this->cell = cell;
			break;
		}
	}
}

void Avatar::GoRight()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row == cell->GetRow() && column + 1 == cell->GetColumn() && cell->CanBeOccupied()) {
			this->cell->Clear();
			column++;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			this->cell = cell;
			break;
		}
	}
}

void Avatar::GoLeft()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row == cell->GetRow() && column - 1 == cell->GetColumn() && cell->CanBeOccupied()) {
			this->cell->Clear();
			column--;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			this->cell = cell;
			break;
		}
	}
}

void Avatar::UsePotion()
{
	if (!canUsePotion()) {
		std::cout << "CAN NOT USE POTION" << std::endl;
		return;
	}

	std::cout << "USED POTION" << std::endl;


	vector <GameEntity*> entities = game->GetEntities();

	for (GameEntity* entity:entities) {
		if (entity->GetTeam() != supportedTeam) continue;

		((Enemy*)entity)->RefillHealth();
	}
	potions--;
}

int Avatar::GetAmountOfPotions()
{
	return potions;
}

bool Avatar::SupportsWerewolves()
{
	return supportedTeam == Werewolves;
}

void Avatar::gotPotion()
{
	potions++;
}

bool Avatar::canUsePotion() const
{
	if (supportedTeam == Vampires && game->IsDay()) return false;

	if (supportedTeam == Werewolves && !game->IsDay()) return false;

	return (potions>0);
}

#include <iostream>
#include <cassert>
#include "Avatar.h"
#include "Game.h"
#include "MapElement.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game, MapElement* cell, bool _supportsWerewolves) : GameEntity(row, column, game, cell), 
	supportsWerewolves(_supportsWerewolves){}

void Avatar::update() {}

void Avatar::Print()
{
	std::cout << "A";
}

Team Avatar::GetTeam()
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

int Avatar::GetAmountOfPotions()
{
	return potions;
}

bool Avatar::SupportsWerewolves()
{
	return supportsWerewolves;
}

void Avatar::gotPotion()
{
	potions++;
}
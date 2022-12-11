#include <iostream>
#include <cassert>
#include "Avatar.h"
#include "Game.h"
#include "MapElement.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game, bool _supportsWerewolves) : GameEntity(row, column, game), 
	supportsWerewolves(_supportsWerewolves){}

void Avatar::update() {}

void Avatar::Print()
{
	std::cout << "A";
}

void Avatar::GoDown()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if(row+1 == cell->GetRow() && column == cell->GetColumn() && cell->CanBeOccupied()) {
			game->ClearCell(row, column);
			row++;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			break;
		}
	}		
}

void Avatar::GoUp()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row - 1 == cell->GetRow() && column == cell->GetColumn() && cell->CanBeOccupied()) {
			game->ClearCell(row, column);
			row--;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			break;
		}
	}
}

void Avatar::GoRight()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row == cell->GetRow() && column + 1 == cell->GetColumn() && cell->CanBeOccupied()) {
			game->ClearCell(row, column);
			column++;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			break;
		}
	}
}

void Avatar::GoLeft()
{
	vector<MapElement*> legalCells = game->GetNeighboringCells(row, column);

	for (auto cell : legalCells) {
		if (row == cell->GetRow() && column - 1 == cell->GetColumn() && cell->CanBeOccupied()) {
			game->ClearCell(row, column);
			column--;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
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
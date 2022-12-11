#include <iostream>
#include <cassert>
#include "Avatar.h"
#include "Game.h"
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
	if (row >= game->GetRows() - 1) return;

	if (game->HasPotion(row + 1, column)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row + 1, column, this);
		row++;
		return;
	}

	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if(row+1 == pair.first && column == pair.second){
			row++;
			game->UpdateEntityPosition(row - 1, column, row, column, this);
		}
	}		
}

void Avatar::GoUp()
{
	if (row == 0) return;

	if (game->HasPotion(row -1, column)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row -1, column, this);
		row--;
		return;
	}
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row - 1 == pair.first && column == pair.second) {
			row--;
			game->UpdateEntityPosition(row + 1, column, row, column, this);
		}
	}
}

void Avatar::GoRight()
{
	if (column >= game->GetColumns() - 1) return;

	if (game->HasPotion(row , column+1)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row, column+1, this);
		column++;
		return;
	}
	
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row == pair.first && column+1 == pair.second) {
			column++;
			game->UpdateEntityPosition(row , column-1, row, column, this);
		}
	}
}

void Avatar::GoLeft()
{
	if (column == 0) return;

	if (game->HasPotion(row , column-1)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row , column-1, this);
		column--;
		return;
	}
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row == pair.first && column -1 == pair.second) {
			column--;
			game->UpdateEntityPosition(row, column+1, row, column, this);
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
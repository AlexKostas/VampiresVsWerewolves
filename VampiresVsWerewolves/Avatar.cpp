#include <cassert>
#include "Avatar.h"
#include "Game.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game)
{
	assert(row >= 0);
	assert(column >= 0);
	assert(game != NULL);

	this->row = row;
	this->column = column;
	this->game = game;
}

void Avatar::update() {
	
}

MapCellType Avatar::GetCellType() {
	return MapCellType::avatar;
}

void Avatar::GoDown()
{
	if (row >= game->GetRows()) return;

	if (game->HasPotion(row + 1, column)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row + 1, column, avatar);
		row++;
		return;
	}

	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	

	for (auto pair : legalCells) {
		if(row+1 == pair.first && column == pair.second){
			row++;
			game->UpdateEntityPosition(row - 1, column, row, column, avatar);
		}
	}
		
}

void Avatar::GoUp()
{
	if (row == 0) return;

	if (game->HasPotion(row -1, column)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row -1, column, avatar);
		row--;
		return;
	}
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row - 1 == pair.first && column == pair.second) {
			row--;
			game->UpdateEntityPosition(row + 1, column, row, column, avatar);
		}
	}
}

void Avatar::GoRight()
{
	if (column >= game->GetColumns()) return;

	if (game->HasPotion(row , column+1)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row, column+1, avatar);
		column++;
		return;
	}
	
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row == pair.first && column+1 == pair.second) {
			column++;
			game->UpdateEntityPosition(row , column-1, row, column, avatar);
		}
	}
	
}

void Avatar::GoLeft()
{
	if (column == 0) return;

	if (game->HasPotion(row , column-1)) {
		gotPotion();
		game->UpdateEntityPosition(row, column, row , column-1, avatar);
		column--;
		return;
	}
	vector<pair<int, int>> legalCells = game->GetAvailableNeighboringCells(row, column);

	for (auto pair : legalCells) {
		if (row == pair.first && column -1 == pair.second) {
			column--;
			game->UpdateEntityPosition(row, column+1, row, column, avatar);
		}
	}
}

int Avatar::GetAmountOfPotions()
{
	return potions;
}

void Avatar::gotPotion()
{
	potions++;
}
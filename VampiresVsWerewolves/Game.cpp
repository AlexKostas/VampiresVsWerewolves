#include <vector>
#include <cassert>
#include "Game.h"
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"
#include "Utils.h"

Game::Game(int row, int column): werewolvesCount((row*column)/15), vampiresCount((row*column)/15)
{
	//TODO CHECK IF THE ROW,COLUMN ARE VALID
	//TODO FIX AVATAR'S INITIALIZATION

	map = new Map(row, column);

	for (int i = 0;i < werewolvesCount;i++) {
		int row,column;

		getValidRandomCoordinates(row, column);

		Werewolf* werewolf = new Werewolf(row,column);

		map->UpdateEntityPosition(row, column,MapCellType::werewolf);

		werewolves.push_back(werewolf);
		entities.push_back(werewolf);
	}

	for (int i = 0;i < vampiresCount;i++) {
		int row, column;
		
		getValidRandomCoordinates(row, column);

		Vampire* vampire = new Vampire(row, column);

		map->UpdateEntityPosition(row, column, MapCellType::vampire);

		vampires.push_back(vampire);
		entities.push_back(vampire);
	}

	int newRow, newColumn;

	getValidRandomCoordinates(newRow, newColumn);

	avatar = new Avatar(newRow, newColumn);
	entities.push_back(avatar);

	map->UpdateEntityPosition(newRow, newColumn, MapCellType::avatar);
}

Game::~Game()
{
	for (int i = 0;i < werewolvesCount;i++)
		delete werewolves[i];	

	for (int i = 0;i < vampiresCount;i++)
		delete vampires[i];

	delete map;
	delete avatar;
}

void Game::Update()
{
	//TODO: change this to iterator
	for (int i = 0; i < entities.size(); i++) {
		int oldRow, oldColumn;
		oldRow = entities[i]->getRow();
		oldColumn = entities[i]->getColumn();

		entities[i]->update();

		int row, column;
		row = entities[i]->getRow();
		column = entities[i]->getColumn();

		map->UpdateEntityPosition(oldRow, oldColumn, row, column, entities[i]->GetCellType());
	}

	map->Show();
}

void Game::getValidRandomCoordinates(int& row, int& column)
{
	int tempRow, tempColumn;

	do {
		Utils::GetRandomCoordinates(map->GetRow(), map->GetColumn(), tempRow, tempColumn);	
	}while(!map->IsGroundCell(tempRow,tempColumn));

	row = tempRow;
	column = tempColumn;
}
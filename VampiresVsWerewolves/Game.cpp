#include <vector>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <ctime>
#include <conio.h>
#include "Game.h"
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"
#include "Utils.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using std::cout;
using std::endl;

Game::Game(int row, int column): werewolvesCount((row*column)/15), vampiresCount((row*column)/15)
{
	//TODO CHECK IF THE ROW,COLUMN ARE VALID
	if (row < 2 || column < 2)
		throw invalid_argument("Invalid Board Size\n");
	
	//TODO FIX AVATAR'S INITIALIZATION

	map = new Map(row, column);

	for (int i = 0;i < werewolvesCount;i++) {
		int row,column;

		getValidRandomCoordinates(row, column);

		Werewolf* werewolf = new Werewolf(row,column, this);

		map->UpdateEntityPosition(row, column,MapCellType::werewolf);

		werewolves.push_back(werewolf);
		entities.push_back(werewolf);
	}

	for (int i = 0;i < vampiresCount;i++) {
		int row, column;
		
		getValidRandomCoordinates(row, column);

		Vampire* vampire = new Vampire(row, column, this);

		map->UpdateEntityPosition(row, column, MapCellType::vampire);

		vampires.push_back(vampire);
		entities.push_back(vampire);
	}

	int newRow, newColumn;

	getValidRandomCoordinates(newRow, newColumn);

	avatar = new Avatar(newRow, newColumn, this);
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

void Game::Run()
{

	float frameTime = (1.0 / frameRate) * CLOCKS_PER_SEC;
	assert(frameTime >= 0);


	clock_t now = clock();
	while (!IsOver())
	{
		while (clock() - now < frameTime);

		now = clock();
		system("cls");
		

		if (_kbhit()) {
			int c;
			switch ((c = _getch())) {

			case KEY_UP:

				//cout << endl << "Up" << endl;//key up
				avatar->GoUp();

				break;

			case KEY_DOWN:

				//cout << endl << "Down" << endl; // key down
				avatar->GoDown();

				break;

			case KEY_LEFT:

				//cout << endl << "Left" << endl; // key left
				avatar->GoLeft();
				break;

			case KEY_RIGHT:

				//cout << endl << "Right" << endl; // key right
				avatar->GoRight();

				break;
			}
		}

		Update();
	}
}

void Game::Update()
{
	for (auto& entity : entities) {
		int oldRow, oldColumn;
		oldRow = entity->getRow();
		oldColumn = entity->getColumn();

		entity->update();

		int row, column;
		row = entity->getRow();
		column = entity->getColumn();

		map->UpdateEntityPosition(oldRow, oldColumn, row, column, entity->GetCellType());
	}

	turnsElapsed++;
	if (turnsElapsed >= turnsToDay) {
		turnsElapsed = 0;
		isDay = !isDay;
	}

	map->Show();
	cout << endl;
	if (isDay) {
		cout << "Day" << endl;
	}
	else {
		cout << "Night" << endl;
	}

	cout << "Potions: " << avatar->GetAmountOfPotions() << endl;
}

bool Game::IsOver()
{
	return vampires.size() == 0 || werewolves.size() == 0;
}

vector<pair<int, int>> Game::GetAvailableNeighboringCells(int row, int col) const
{
	return map->GetLegalNeighborCells(row, col);
}

vector<pair<int, int>> Game::GetAvailableDiagonalNeighboringCells(int row, int col) const
{
	return map->GetAvailableDiagonalNeighboringCells(row, col);
}

int Game::GetRows()
{

	return map->GetRow();
}

int Game::GetColumns()
{
	return map->GetColumn();
}

void Game::UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity)
{
	map->UpdateEntityPosition(oldRow, oldColumn, newRow, newColumn, entity);
}

bool Game::HasPotion(int row, int col) const
{
	
	return map->HasPotion(row,col);
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
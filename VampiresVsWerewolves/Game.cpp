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

Game::Game(int row, int column)
{
	//TODO CHECK IF THE ROW,COLUMN ARE VALID
	if (row < 2 || column < 2)
		throw invalid_argument("Invalid Board Size\n");
	
	//TODO FIX AVATAR'S INITIALIZATION

	map = new Map(row, column);

	/*for (int i = 0;i < werewolvesCount;i++) {
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

	map->UpdateEntityPosition(newRow, newColumn, MapCellType::avatar);*/
}

Game::~Game()
{
	/*for (int i = 0;i < werewolvesCount;i++)
		delete werewolves[i];	

	for (int i = 0;i < vampiresCount;i++)
		delete vampires[i];

	delete map;
	delete avatar;*/
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
		Update();

		//TODO: add to separate function
		if (!_kbhit()) continue;

		int c;
		switch ((c = _getch())) {

		case KEY_UP:

			cout << endl << "Up" << endl;//key up
			break;

		case KEY_DOWN:

			cout << endl << "Down" << endl; // key down
			break;

		case KEY_LEFT:

			cout << endl << "Left" << endl; // key left
			break;

		case KEY_RIGHT:

			cout << endl << "Right" << endl; // key right
			break;
		}
	}
}

void Game::Update()
{
	turnsElapsed++;
	if (turnsElapsed >= turnsToDay) {
		turnsElapsed = 0;
		isDay = !isDay;
	}

	map->Update();
}

bool Game::IsOver()
{
	return false;
	//return vampires.size() == 0 || werewolves.size() == 0;
}

vector<pair<int, int>> Game::GetAvailableNeighboringCells(int row, int col) const
{
	return map->GetLegalNeighborCells(row, col);
}

void Game::getValidRandomCoordinates(int& row, int& column)
{
	/*int tempRow, tempColumn;

	do {
		Utils::GetRandomCoordinates(map->GetRow(), map->GetColumn(), tempRow, tempColumn);	
	}while(!map->IsGroundCell(tempRow,tempColumn));

	row = tempRow;
	column = tempColumn;*/
}
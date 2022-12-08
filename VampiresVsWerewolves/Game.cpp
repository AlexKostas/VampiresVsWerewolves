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
#define ESC 27

using std::cout;
using std::endl;

Game::Game(int row, int column): werewolvesCount((row*column)/15), vampiresCount((row*column)/15)
{
	//TODO CHECK IF THE ROW,COLUMN ARE VALID
	if (row < 2 || column < 2)
		throw invalid_argument("Invalid Board Size\n");
	
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

	bool supportsWerewolf;
	do {
		cout << "Choose your team. V for vampires or W for werewolves" << endl;

		string input;
		cin >> input;

		if (input == "V" || input=="v") {
			supportsWerewolf = false;
			break;
		}
		else if (input == "W"|| input=="w") {
			supportsWerewolf = true;
			break;
		}
	} while (true);

	int newRow, newColumn;

	getValidRandomCoordinates(newRow, newColumn);

	avatar = new Avatar(newRow, newColumn, this, supportsWerewolf);
	entities.push_back(avatar);

	map->UpdateEntityPosition(newRow, newColumn, MapCellType::avatar);


	clock_t now = clock();
	// GAME LOOP
	while (!IsOver())
	{
		while (clock() - now < frameTime);

		now = clock();
		
		bool gameTerminatedByPlayer = false;
		if (_kbhit()) {
			int c;
			switch ((c = _getch())) {

			case KEY_UP:
				avatar->GoUp();
				break;

			case KEY_DOWN:
				avatar->GoDown();
				break;

			case KEY_LEFT:
				avatar->GoLeft();
				break;

			case KEY_RIGHT:
				avatar->GoRight();
				break;

			case ESC:
				gameTerminatedByPlayer = true;
				break;

			case '\t':
				isPaused = !isPaused;
				cout << "\nGAME IS PAUSED! Press Tab to continue..." << endl;

				string team = (avatar->SupportsWerewolves()) ? "Werewolves" : "Vampires";

				cout << "You support " <<  team << "!" << endl;
				cout << "Number of Vampires: " << vampires.size() << endl;
				cout << "Number of Werewolves: " << werewolves.size() << endl;
				break;
			}
		}

		if (gameTerminatedByPlayer) break;

		if (!isPaused) { 
			system("cls");
			Update(); 
		}
	}
	
	if (werewolves.size() == 0 && vampires.size() == 0) {
		cout << "\nITS A DRAW!!";
	}
	else if (vampires.size() == 0) {
		cout << "\nVAMPIRES WON!!" << endl;
	}
	else if (werewolves.size() == 0)
		cout << "\nWEREWOLVES WON!!" << endl;
	else
		cout << "GAME TERMINATED EARLY" << endl;
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
		cout << "Turns to night: " << turnsToDay - turnsElapsed << endl;
	}
	else {
		cout << "Night" << endl;
		cout << "Turns to day: " << turnsToDay - turnsElapsed << endl;
	}

	cout << "Potions: " << avatar->GetAmountOfPotions() << endl << endl;

	cout << "Press Tab to pause or ESC to exit" << endl;
	
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
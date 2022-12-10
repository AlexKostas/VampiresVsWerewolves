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
#define MIN_BOARD_SIZE 4

using std::cout;
using std::endl;

Game::Game(int row, int column): werewolvesCount((row*column)/15), vampiresCount((row*column)/15)
{
	if (row < MIN_BOARD_SIZE || column < MIN_BOARD_SIZE)
		throw invalid_argument("Invalid Board Size\n");
	
	map = new Map(row, column);

	createWerewolves();
	createVampires();
	createAvatar();
}

Game::~Game()
{
	for (GameEntity* entity : entities)
		delete entity;

	delete map;
}

void Game::Run()
{
	float frameTime = (1.0 / frameRate) * CLOCKS_PER_SEC;
	assert(frameTime >= 0);

	clock_t now = clock();

	// GAME LOOP
	while (!isOver())
	{
		// Wait for next frame
		while (clock() - now < frameTime);
		now = clock();
		
		// If player asked to exit handleInput returns true
		// so we need to exit the game loop
		if (handleInput()) break;

		// Update the state of the game as long
		// as it is not paused
		if (!isPaused) { 
			system("cls");
			update(); 
		}
	}

	displayEndOfGameMessages();
}

void Game::update()
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

/// <summary>
/// Responsible for handling input from the user. Returns true if the user
/// asked for the game to end.
/// </summary>
bool Game::handleInput()
{
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

			cout << "You support " << team << "!" << endl;
			cout << "Number of Vampires: " << vampires.size() << endl;
			cout << "Number of Werewolves: " << werewolves.size() << endl;

			for (Vampire* vampire : vampires)
				vampire->DisplayHealth();

			for (Werewolf* werewolf : werewolves)
				werewolf->DisplayHealth();

			break;
		}
	}

	return gameTerminatedByPlayer;
}

bool Game::isOver()
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

vector<Enemy*> Game::GetNeighboringWerewolves(int row, int col)
{
	assert(row >= 0 && row < map->GetRow());
	assert(col >= 0 && col < map->GetColumn());
	vector<Enemy*> result;

	for (Werewolf* werewolf : werewolves)
		if (Utils::ManhattanDistance(werewolf->getRow(), row, werewolf->getColumn(), col) == 1)
			result.push_back(werewolf);
	
	return result;
}

vector<Enemy*> Game::GetNeighboringVampires(int row, int col)
{
	assert(row >= 0 && row < map->GetRow());
	assert(col >= 0 && col < map->GetColumn());
	vector<Enemy*> result;

	for (Vampire* vampire : vampires)
		if (Utils::ManhattanDistance(vampire->getRow(), row, vampire->getColumn(), col) == 1)
			result.push_back(vampire);

	return result;
}

int Game::GetRows() const
{
	return map->GetRow();
}

int Game::GetColumns() const
{
	return map->GetColumn();
}

void Game::UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity)
{
	map->UpdateEntityPosition(oldRow, oldColumn, newRow, newColumn, entity);
}

void Game::OnEntityDied(GameEntity* self)
{
	map->UpdateEntityPosition(self->getRow(), self->getColumn(), ground);

	for (auto entity = entities.begin(); entity != entities.end(); entity++)
		if (*entity == self) {
			entities.erase(entity);
			break;
		}

	for (auto entity = vampires.begin(); entity != vampires.end(); entity++)
		if (*entity == self) {
			vampires.erase(entity);
			break;
		}

	for (auto entity = werewolves.begin(); entity != werewolves.end(); entity++)
		if (*entity == self) {
			werewolves.erase(entity);
			break;
		}
}

bool Game::HasPotion(int row, int col) const
{	
	return map->HasPotion(row,col);
}

void Game::createVampires()
{
	for (int i = 0; i < vampiresCount; i++) {
		pair<int, int> coords = map->GetRandomAvailableCell();
		int newRow = coords.first, newColumn = coords.second;

		Vampire* vampire = new Vampire(newRow, newColumn, this);

		map->UpdateEntityPosition(newRow, newColumn, MapCellType::vampire);

		vampires.push_back(vampire);
		entities.push_back(vampire);
	}
}

void Game::createWerewolves()
{
	for (int i = 0; i < werewolvesCount; i++) {
		pair<int, int> coords = map->GetRandomAvailableCell();
		int newRow = coords.first, newColumn = coords.second;

		Werewolf* werewolf = new Werewolf(newRow, newColumn, this);

		map->UpdateEntityPosition(newRow, newColumn, MapCellType::werewolf);

		werewolves.push_back(werewolf);
		entities.push_back(werewolf);
	}
}

void Game::createAvatar()
{
	bool supportsWerewolf;
	do {
		cout << "Choose your team. V for vampires or W for werewolves" << endl;

		string input;
		cin >> input;

		if (input == "V" || input == "v") {
			supportsWerewolf = false;
			break;
		}
		else if (input == "W" || input == "w") {
			supportsWerewolf = true;
			break;
		}
	} while (true);

	pair<int, int> coords = map->GetRandomAvailableCell();
	int newRow = coords.first, newColumn = coords.second;

	avatar = new Avatar(newRow, newColumn, this, supportsWerewolf);
	entities.push_back(avatar);

	map->UpdateEntityPosition(newRow, newColumn, MapCellType::avatar);
}

void Game::displayEndOfGameMessages() const
{
	if (werewolves.size() == 0 && vampires.size() == 0)
		cout << endl << "ITS A DRAW!!";
	else if (vampires.size() == 0)
		cout << endl << "WEREWOLVES WON!!" << endl;
	else if (werewolves.size() == 0)
		cout << endl << "VAMPIRES WON!!" << endl;
	else
		cout << endl << "GAME TERMINATED EARLY" << endl;
}
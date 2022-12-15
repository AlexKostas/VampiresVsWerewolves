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
#include "MapElement.h"
#include "Utils.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27
#define TAB 9
#define MIN_BOARD_SIZE 4
#define POTION_KEY 107 //it is the key k of english

using std::cout;
using std::endl;

Game::Game(int row, int column): startingWerewolves((row*column)/15), startingVampires((row*column)/15)
{
	if (row < MIN_BOARD_SIZE || column < MIN_BOARD_SIZE)
		throw invalid_argument("Invalid Board Size\n");
	
	map = new Map(row, column);

	createEntity<Werewolf>(startingWerewolves);
	numberOfWerewolves = startingWerewolves;

	createEntity<Vampire>(startingVampires);
	numberOfVampires = startingVampires;

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
		if (!isPaused) 
			update(); 
	}

	displayEndOfGameMessages();
}

void Game::update()
{
	for (GameEntity* entity : entities) 
		entity->update();

	turnsElapsed++;
	if (turnsElapsed >= turnsToDay) {
		turnsElapsed = 0;
		isDay = !isDay;
	}

	map->Show();
	displayFrameMessages();
}

/// <summary>
/// Responsible for handling input from the user. Returns true if the user
/// asked for the game to end.
/// </summary>
bool Game::handleInput()
{
	bool gameTerminatedByPlayer = false;

	// If there is at least one character in input buffer
	if (_kbhit()) {
		//this is for the inputs  from keybord
		int c;
		switch ((c = _getch())) {

		case KEY_UP:
			if(!isPaused) avatar->GoUp();
			break;

		case KEY_DOWN:
			if (!isPaused) avatar->GoDown();
			break;

		case KEY_LEFT:
			if (!isPaused) avatar->GoLeft();
			break;

		case KEY_RIGHT:
			if (!isPaused) avatar->GoRight();
			break;

		case ESC:
			gameTerminatedByPlayer = true;
			break;
		case POTION_KEY:
			avatar->UsePotion();
			break;

		case TAB:
			isPaused = !isPaused;
			displayPauseMessages();
			break;
		}
	}

	return gameTerminatedByPlayer;
}

bool Game::isOver()
{
	return numberOfVampires == 0 || numberOfWerewolves == 0;
}

vector<MapElement*> Game::GetNeighboringCells(int row, int column) const
{
	return map->GetNeighboringCells(row, column);
}

vector<MapElement*> Game::GetNeighboringDiagonalCells(int row, int column) const
{
	return map->GetNeighboringDiagonalCells(row, column);
}

vector<GameEntity*> Game::GetEntities() const
{
	return entities;
}

void Game::OnEntityDied(GameEntity* self)
{
	if (self->GetTeam() == Vampires) numberOfVampires--;
	else if (self->GetTeam() == Werewolves) numberOfWerewolves--;
	else assert(false); // There is an error if dead entity isn't vampire or werewolf

	// Remove dead entity from entities list
	for (auto entity = entities.begin(); entity != entities.end(); entity++) {
		if (*entity == self) {
			entities.erase(entity);
			break; // We exit loop because there can't be another entity of this type in the list
		}
	}
}

bool Game::IsDay() const
{
	return isDay;
}

template <class EntityType>
void Game::createEntity(int numberOfEntities) {
	for (int i = 0; i < numberOfEntities; i++) {
		MapElement* cell = map->GetRandomAvailableCell();
		int newRow = cell->GetRow(), newColumn = cell->GetColumn();

		EntityType* entity = new EntityType(newRow, newColumn, this, cell);

		cell->SetOccupant(entity);

		entities.push_back(entity);
	}
}

void Game::createAvatar()
{
	Team supportedTeam = readTeamChoiceFromInput();

	MapElement* cell = map->GetRandomAvailableCell();
	assert(cell->CanBeOccupied());
	int newRow = cell->GetRow(), newColumn = cell->GetColumn();

	avatar = new Avatar(newRow, newColumn, this, cell, supportedTeam);
	entities.push_back(avatar);

	cell->SetOccupant(avatar);
}

Team Game::readTeamChoiceFromInput() const
{
	Team supportedTeam;
	do {
		cout << "Choose your team. V for vampires or W for werewolves" << endl;

		string input;
		cin >> input;

		if (input == "V" || input == "v") {
			supportedTeam = Vampires;
			break;
		}
		else if (input == "W" || input == "w") {
			supportedTeam = Werewolves;
			break;
		}
	} while (true);

	return supportedTeam;
}

void Game::displayFrameMessages() const
{
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

void Game::displayPauseMessages() const
{
	cout << "\nGAME IS PAUSED! Press Tab to continue..." << endl;


	cout << "You support ";
	avatar->PrintSupportedTeam();
	cout << "!" << endl;
	cout << "Number of Vampires: " << numberOfVampires << endl;
	cout << "Number of Werewolves: " << numberOfWerewolves << endl;

	cout << endl;
	for (GameEntity* entity : entities)
		entity->DisplayInfo();
}

void Game::displayEndOfGameMessages() const
{
	if (numberOfWerewolves == 0 && numberOfVampires == 0)
		cout << endl << "ITS A DRAW!!";
	else if (numberOfVampires == 0)
		cout << endl << "WEREWOLVES WON!!" << endl;
	else if (numberOfWerewolves == 0)
		cout << endl << "VAMPIRES WON!!" << endl;
	else
		cout << endl << "GAME TERMINATED EARLY" << endl;
}
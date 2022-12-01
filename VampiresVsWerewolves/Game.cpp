#include <vector>
#include "Game.h"
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"

Game::Game(unsigned int row, unsigned column): werewolvesCount(row*column/15), vampiresCount(row*column/15)
{
	//TODO CHECK IF THE ROW,COLUMN ARE VALID

	map = new Map(row, column);

	for (int i = 0;i < werewolvesCount;i++) {
		Werewolf* werewolf = new Werewolf(0, 0);

		werewolves.push_back(werewolf);
	}

	for (int i = 0;i < vampiresCount;i++) {
		Vampire* vampire = new Vampire(1, 2);

		vampires.push_back(vampire);
	}

	//TEMP

	Update();
}

Game::~Game()
{

	for (int i = 0;i < werewolvesCount;i++) {
		delete werewolves[i];
	}

	for (int i = 0;i < vampiresCount;i++) {
		delete vampires[i];
	}

	delete map;
}

void Game::Update()
{
	for (int i = 0;i < werewolvesCount;i++) {

		unsigned int oldRow, oldColumn;
		oldRow = werewolves[i]->getRow();
		oldColumn = werewolves[i]->getColumn();

		werewolves[i]->update();

		unsigned int row, column;
		row = werewolves[i]->getRow();
		column = werewolves[i]->getColumn();


		map->UpdateEntityPosition(oldRow, oldColumn, row, column, werewolf);
	}

	for (int i = 0;i < vampiresCount;i++) {
		vampires[i]->update();

		unsigned int oldRow, oldColumn;
		oldRow = vampires[i]->getRow();
		oldColumn = vampires[i]->getColumn();

		vampires[i]->update();

		unsigned int row, column;
		row = vampires[i]->getRow();
		column = vampires[i]->getColumn();


		map->UpdateEntityPosition(oldRow, oldColumn, row, column, vampire);
	}

	map->Show();
}

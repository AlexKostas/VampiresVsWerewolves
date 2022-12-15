#include <iostream>
#include <cassert>
#include "Avatar.h"
#include "Enemy.h"
#include "Game.h"
#include "MapElement.h"
#include "Utils.h"

Avatar::Avatar(int row, int column, Game* game, MapElement* cell, Team _supportedTeam) : GameEntity(row, column, game, cell), 
	supportedTeam(_supportedTeam){}

void Avatar::update() {
	// Update does nothing for this assignment since avatar is only moved when 
	// player asks to. If he was moving independently from the player, then this
	// logic would be placed here.
}

void Avatar::Print() const
{
	// Print A with a red color
	std::cout << "\033[1;31mA\033[0m";
}

void Avatar::DisplayInfo() const{}

Team Avatar::GetTeam() const
{
	return Neutral;
}

void Avatar::GoDown()
{
	moveTo(row + 1, column);
}

void Avatar::GoUp()
{
	moveTo(row - 1, column);
}

void Avatar::GoRight()
{
	moveTo(row, column + 1);
}

void Avatar::GoLeft()
{
	moveTo(row, column - 1);
}

void Avatar::moveTo(int row, int col)
{
	// Get where we can go from current position
	vector<MapElement*> legalCells = game->GetNeighboringCells(this->row, this->column);

	// Check if target cell is in the legal moves list. If so, do the move.
	for (auto cell : legalCells) {
		if (row == cell->GetRow() && col == cell->GetColumn() && cell->CanBeOccupied()) {
			this->cell->Clear();
			this->row = row;
			this->column = col;

			if (cell->HasPotion()) {
				gotPotion();
				cell->RemovePotion();
			}

			cell->SetOccupant(this);
			this->cell = cell;
			break;
		}
	}
}

void Avatar::UsePotion()
{
	if (!canUsePotion()) {
		std::cout << "CAN NOT USE POTION" << std::endl;
		return;
	}

	std::cout << "USED POTION" << std::endl;

	vector <GameEntity*> entities = game->GetEntities();

	for (GameEntity* entity:entities) {
		if (entity->GetTeam() != supportedTeam) continue;

		((Enemy*)entity)->RefillHealth();
	}
	potions--;
}

int Avatar::GetAmountOfPotions()
{
	return potions;
}

void Avatar::PrintSupportedTeam()
{
	string supportedTeamText = (supportedTeam == Werewolves) ? "Werewolves" : "Vampires";
	std::cout << supportedTeamText;
}

void Avatar::gotPotion()
{
	potions++;
}

bool Avatar::canUsePotion() const
{
	//vampires heal at night
	if (supportedTeam == Vampires && game->IsDay()) return false;
	//werewolves heal at day
	if (supportedTeam == Werewolves && !game->IsDay()) return false;

	return (potions>0);
}

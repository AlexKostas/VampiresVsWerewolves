#pragma once
#include <vector>
#include <utility>
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"

using namespace std;

class Game {
public:
	Game(int row, int column);
	~Game();
	void Update();
	bool IsOver();
	vector<pair<int, int>> GetAvailableNeighboringCells(int row, int col) const;

private:
	const int werewolvesCount;
	const int vampiresCount;
	const int turnsToDay = 15;
	int turnsElapsed = 0;
	bool isDay = true;

	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	vector<GameEntity*> entities;
	Avatar* avatar;
	
	void getValidRandomCoordinates(int& row, int& column);
};
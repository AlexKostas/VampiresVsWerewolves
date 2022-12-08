#pragma once
#include <vector>
#include <utility>
#include "Map.h"

using namespace std;

class GameEntity;
class Avatar;
class Vampire;
class Werewolf;

class Game {
public:
	Game(int row, int column);
	~Game();
	void Run();
	vector<pair<int, int>> GetAvailableNeighboringCells(int row, int col) const;

private:
	const int turnsToDay = 15;
	const int frameRate = 2;
	int turnsElapsed = 0;
	bool isDay = true;

	Map* map;
	
	void Update();
	bool IsOver();
};
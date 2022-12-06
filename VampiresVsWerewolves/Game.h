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
	vector<pair<int, int>> GetAvailableNeighboringCells() const;

private:
	const int werewolvesCount;
	const int vampiresCount;
	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	vector<GameEntity*> entities;
	Avatar* avatar;
	
	void getValidRandomCoordinates( int& row, int& column);
};
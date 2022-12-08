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
	vector<pair<int, int>> GetAvailableDiagonalNeighboringCells(int row, int col)const;
	int GetRows();
	int GetColumns();
	void UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity);
	bool HasPotion(int row, int col)const;

private:
	const int werewolvesCount;
	const int vampiresCount;
	const int turnsToDay = 15;
	const int frameRate = 2;
	int turnsElapsed = 0;
	bool isDay = true;

	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	vector<GameEntity*> entities;
	Avatar* avatar;
	
	void getValidRandomCoordinates(int& row, int& column);
	void Update();
	bool IsOver();
};
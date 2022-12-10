#pragma once
#include <vector>
#include <utility>
#include "Map.h"

using namespace std;

class GameEntity;
class Avatar;
class Enemy;
class Werewolf;
class Vampire;

class Game {
public:
	Game(int row, int column);
	~Game();
	void Run();
	vector<pair<int, int>> GetAvailableNeighboringCells(int row, int col) const;
	vector<pair<int, int>> GetAvailableDiagonalNeighboringCells(int row, int col) const;
	vector<Enemy*> GetNeighboringWerewolves(int row, int col);
	vector<Enemy*> GetNeighboringVampires(int row, int col);
	int GetRows() const;
	int GetColumns() const;
	void UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity);
	void OnEntityDied(GameEntity* self);
	bool HasPotion(int row, int col) const;

private:
	const int werewolvesCount;
	const int vampiresCount;
	const int turnsToDay = 15;
	const int frameRate = 5;
	int turnsElapsed = 0;
	bool isDay = true;
	bool isPaused = false;

	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	vector<GameEntity*> entities;
	Avatar* avatar;
	
	void createVampires();
	void createWerewolves();
	void createAvatar();
	void update();
	bool handleInput();
	bool isOver();
	void displayEndOfGameMessages() const;
};
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

	vector<MapElement*> GetNeighboringCells(int row, int column) const;
	vector<MapElement*> GetNeighboringDiagonalCells(int row, int column) const;

	void OnEntityDied(GameEntity* self);

private:
	const int startingWerewolves;
	const int startingVampires;
	const int turnsToDay = 15;
	const int frameRate = 5;

	int numberOfVampires = 0;
	int numberOfWerewolves = 0;

	int turnsElapsed = 0;

	bool isDay = true;
	bool isPaused = false;

	Map* map;
	vector<GameEntity*> entities;
	Avatar* avatar;
	
	void createVampires();
	void createWerewolves();
	void createAvatar();
	void update();
	bool handleInput();
	bool isOver();
	void displayFrameMessages() const;
	void displayEndOfGameMessages() const;
};
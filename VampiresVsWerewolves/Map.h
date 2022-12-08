#pragma once
#include <utility>
#include <vector>

class GameEntity;
class Werewolf;
class Vampire;
class Avatar;

using namespace std;

class Map {
public:
	Map(int rows, int columns);
	~Map();
	void Update();
	vector<pair<int, int>> GetLegalNeighborCells(int row, int col) const;
	int GetRow() const;
	int GetColumn() const;
private:
	const int werewolvesCount;
	const int vampiresCount;
	const int treeDensity=5;
	const int waterDensity =5;
	int rows, columns;
	GameEntity*** board; 

	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	Avatar* avatar;

	void populateMap();
	void printBorderRow() const;
	void printCellRow(int row) const;

	bool cellAboveIsAvailable(int row, int column) const;
	bool cellBelowIsAvailable(int row, int column) const;
	bool cellLeftIsAvailable(int row, int column) const;
	bool cellRightIsAvailable(int row, int column) const;
	void Show() const;
};
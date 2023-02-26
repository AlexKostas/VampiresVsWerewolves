#pragma once
#include <utility>
#include <vector>
#include "Enums.h"

using namespace std;

class MapElement;
class GameEntity;

class Map {
public:
	Map(int rows, int columns);
	~Map();

	void Show() const;

	vector<MapElement*> GetNeighboringCells(int row, int column) const;
	vector<MapElement*> GetNeighboringDiagonalCells(int row, int column) const;

	MapElement* GetRandomAvailableCell() const;

private:
	const int treeDensity=5;
	const int waterDensity =5;
	const int startingAmountOfPotions = 1;

	int rows, columns;
	MapElement*** board; //2D Array of pointers to MapElement objects

	void populateMap();
	void printCellRow(int row) const;

	template <class TerrainElement>
	void placeElements(int elementCount);
	void placePotions();

	bool cellAboveIsAvailable(int row, int column) const;
	bool cellBelowIsAvailable(int row, int column) const;
	bool cellLeftIsAvailable(int row, int column) const;
	bool cellRightIsAvailable(int row, int column) const;

	bool cellAboveRightIsAvailable(int row, int column) const;
	bool cellAboveLeftIsAvailable(int row, int column) const;
	bool cellBelowRightIsAvailable(int row, int column) const;
	bool cellBelowLeftIsAvailable(int row, int column) const;
};
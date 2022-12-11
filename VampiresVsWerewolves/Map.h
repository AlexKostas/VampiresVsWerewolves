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

	void UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, GameEntity* entity);
	void UpdateEntityPosition(int newRow, int newColumn, GameEntity* entity);
	void ClearCell(int row, int column);

	vector<pair<int, int>> GetLegalNeighborCells(int row, int col) const;
	vector<pair<int, int>> GetAvailableDiagonalNeighboringCells(int row, int col) const;
	pair<int, int> GetRandomAvailableCell();

	int GetRow() const;
	int GetColumn() const;

	bool HasPotion(int row,int col) const;
	void RemovePotion(int row, int col);
private:
	const int treeDensity=5;
	const int waterDensity =5;
	const int startingAmountOfPotions = 2;
	int rows, columns;
	MapElement*** board; 

	void populateMap();
	void printBorderRow() const;
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
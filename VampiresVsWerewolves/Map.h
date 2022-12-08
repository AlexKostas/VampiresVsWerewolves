#pragma once
#include <utility>
#include <vector>
#include "Enums.h"

using namespace std;

class Map {
public:
	Map(int rows, int columns);
	~Map();
	void Show() const;
	void UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity);
	void UpdateEntityPosition(int newRow, int newColumn, MapCellType entity);
	vector<pair<int, int>> GetLegalNeighborCells(int row, int col) const;
	vector<pair<int, int>> GetAvailableDiagonalNeighboringCells(int row, int col) const;
	bool IsGroundCell(int row, int column) const;
	int GetRow() const;
	int GetColumn() const;
	bool HasPotion(int row,int col) const;
private:
	const int treeDensity=5;
	const int waterDensity =5;
	const int amountOfPotions = 2;
	int rows, columns;
	MapCellType** board; 

	void populateMap();
	void printBorderRow() const;
	void printCellRow(int row) const;
	void placeElements(int elementCount, MapCellType element);
	char getCellChar(int row, int column) const;

	bool cellAboveIsAvailable(int row, int column) const;
	bool cellBelowIsAvailable(int row, int column) const;
	bool cellLeftIsAvailable(int row, int column) const;
	bool cellRightIsAvailable(int row, int column) const;

	bool cellAboveRightIsAvailable(int row, int column) const;
	bool cellAboveLeftIsAvailable(int row, int column) const;
	bool cellBelowRightIsAvailable(int row, int column) const;
	bool cellBelowLeftIsAvailable(int row, int column) const;
};
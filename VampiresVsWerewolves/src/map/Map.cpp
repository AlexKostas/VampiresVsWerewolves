#include <iostream>
#include <math.h>
#include <cassert>
#include "Utils.h"
#include "Map.h"
#include "MapElement.h"
#include "Ground.h"
#include "Water.h"
#include "Tree.h"

using namespace std;

Map::Map(int x, int y) : rows(x), columns(y) {
	// Create 2D dynamic array of pointers to Map Element object
	board = new MapElement** [x];

	for (int i = 0;i < x;i++)
		board[i] = new MapElement*[y];

	// Initialize whole board with ground
	for (int i = 0;i < x;i++)
		for (int j = 0;j < y;j++)
			board[i][j] = new Ground(i, j);

	populateMap();
}

Map::~Map() {
	// Delete map elements
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			delete board[i][j];

	// Delete 2D array
	for (int i = 0;i < rows;i++)
		delete[] board[i];

	delete[] board;
}

void Map::Show() const {
	system("cls");
	cout << "\033[1;1H"; // Move cursor to top left

	for (int row = 0; row < rows; row++) 
		printCellRow(row);
}

vector<MapElement*> Map::GetNeighboringCells(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	vector<MapElement*> result;

	if (cellAboveIsAvailable(row, col))
		result.push_back(board[row-1][col]);

	if (cellBelowIsAvailable(row, col)) 
		result.push_back(board[row+1][col]);
	
	if (cellLeftIsAvailable(row, col))
		result.push_back(board[row][col-1]);

	if (cellRightIsAvailable(row, col))
		result.push_back(board[row][col + 1]);

	return result;
}

vector<MapElement*> Map::GetNeighboringDiagonalCells(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	vector<MapElement*> result;

	if (cellAboveLeftIsAvailable(row, col)) 
		result.push_back(board[row-1][col-1]);

	if (cellAboveRightIsAvailable(row, col)) 
		result.push_back(board[row-1][col+1]);

	if (cellBelowLeftIsAvailable(row, col)) 
		result.push_back(board[row+1][col-1]);

	if (cellBelowRightIsAvailable(row, col)) 
		result.push_back(board[row+1][col+1]);

	return result;
}

MapElement* Map::GetRandomAvailableCell() const
{
	int x, y;
	// Try random coordinates until an available cell is found
	do {
		// Writes results into x and y
		Utils::GetRandomCoordinates(rows, columns, x, y);
	} while (!board[x][y]->CanBeOccupied());

	return board[x][y];
}

void Map::populateMap()
{
	int numberOfTrees = round((rows * columns) * (treeDensity / 100.0));
	int numberOfWaterCells = round((rows * columns) * (waterDensity / 100.0));

	placeElements<Tree>(numberOfTrees);
	placeElements<Water>(numberOfWaterCells);
	placePotions();
}

void Map::printCellRow(int row) const {
	for (int col = 0; col < columns; col++)
		board[row][col]->Print();
	cout << endl;
}

template <class TerrainElement>
void Map::placeElements(int elementCount)
{
	for (int i = 0; i < elementCount; i++) {
		MapElement* cell = GetRandomAvailableCell();
		int row = cell->GetRow();
		int col = cell->GetColumn();

		//delete cell;
		board[row][col] = new TerrainElement(row, col);
	}
}

void Map::placePotions() {
	for (int i = 0; i < startingAmountOfPotions; i++) {
		MapElement* cell = GetRandomAvailableCell();
		cell->PlacePotion();
	}
}

bool Map::cellBelowIsAvailable(int row, int column) const
{
	if (row + 1 >= rows) return false;
	assert(column >= 0 && column < columns);

	return true;
}

bool Map::cellAboveIsAvailable(int row, int column) const
{
	if (row - 1 < 0) return false;
	assert(columns >= 0 && column < columns);

	return true;
}

bool Map::cellLeftIsAvailable(int row, int column) const
{
	if (column - 1 < 0) return false;
	assert(row >= 0 && row < rows);

	return true;
}

bool Map::cellRightIsAvailable(int row, int column) const
{
	if (column +1 >= columns) return false;
	assert(row >= 0 && row < rows);
	return true;
}

bool Map::cellAboveRightIsAvailable(int row, int column) const
{
	if(row<=0 || column >= columns-1) return false;
	return true;
}

bool Map::cellAboveLeftIsAvailable(int row, int column) const
{
	if (row <= 0 || column <= 0) return false;
	return true;
}

bool Map::cellBelowRightIsAvailable(int row, int column) const
{
	if (row >= rows - 1 || column >= columns - 1) return false;
	return true;
}

bool Map::cellBelowLeftIsAvailable(int row, int column) const
{
	if (row >= rows - 1 || column <= 0) return false;
	return true;
}
#include <iostream>
#include <math.h>
#include <cassert>
#include <utility>
#include "Utils.h"
#include "Map.h"

using namespace std;

Map::Map( int x, int y) {
	this->rows = x;
	this->columns = y;

	board = new MapCellType* [x];

	for (int i = 0;i < x;i++)
		board[i] = new MapCellType[y];

	for (int i = 0;i < x;i++)
		for (int j = 0;j < y;j++)
			board[i][j] = ground;

	populateMap();
}

Map::~Map() {
	for (int i = 0;i < rows;i++)
		delete[] board[i];

	delete[] board;
}

void Map::Show() const {	
	for (int row = 0; row < rows; row++) {
		printBorderRow();
		printCellRow(row);
	}
	printBorderRow();
}

void Map::UpdateEntityPosition(int oldRow, int oldColumn, int newRow, int newColumn, MapCellType entity)
{
	board[oldRow][oldColumn] = ground;
	UpdateEntityPosition(newRow, newColumn, entity);
}

void Map::UpdateEntityPosition(int newRow, int newColumn, MapCellType entity)
{
	board[newRow][newColumn] = entity;
}

vector<pair<int, int>> Map::GetLegalNeighborCells(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	vector<pair<int, int>> result;

	if (cellAboveIsAvailable(row, col)) {
		pair<int, int> coords(row - 1, col);
		result.push_back(coords);
	}
	if (cellBelowIsAvailable(row, col)) {
		pair<int, int> coords(row + 1, col);
		result.push_back(coords);
	}
	if (cellLeftIsAvailable(row, col)) {
		pair<int, int> coords(row, col - 1);
		result.push_back(coords);
	}
	if(cellRightIsAvailable(row, col)) {
		pair<int, int> coords(row, col + 1);
		result.push_back(coords);
	}

	return result;
}

vector<pair<int, int>> Map::GetAvailableDiagonalNeighboringCells(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	vector<pair<int, int>> result;

	if (cellAboveLeftIsAvailable(row, col)){
		pair<int,int> coords(row-1,col-1);
		result.push_back(coords);
	}
	if (cellAboveRightIsAvailable(row, col)) {
		pair<int, int> coords(row - 1, col +1);
		result.push_back(coords);
	}
	if (cellBelowLeftIsAvailable(row, col)) {
		pair<int, int> coords(row +1, col - 1);
		result.push_back(coords);
	}
	if (cellBelowRightIsAvailable(row, col)) {
		pair<int, int> coords(row + 1, col +1);
		result.push_back(coords);
	}

	return result;
}

pair<int, int> Map::GetRandomAvailableCell()
{
	int x, y;
	do {
		Utils::GetRandomCoordinates(rows, columns, x, y);
	} while (board[x][y] != ground);

	return pair<int, int>(x, y);
}

int Map::GetRow() const
{
	return rows;
}

int Map::GetColumn() const
{
	return columns;
}

bool Map::HasPotion(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	return board[row][col]==potion;
}

void Map::populateMap()
{
	int numberOfTrees = round((rows * columns) * (treeDensity / 100.0));
	int numberOfWaterCells = round((rows * columns) * (waterDensity / 100.0));

	placeElements(numberOfTrees, tree);
	placeElements(numberOfWaterCells, water);
	placeElements(amountOfPotions, potion);
}

void Map::printBorderRow() const {
	for (int col = 0; col < columns; col++)
		cout << "+" << "===";		

	cout << "+" << endl;
}

void Map::printCellRow(int row) const {
	for (int col = 0; col < columns; col++) {
		cout << "|" << " ";

		char cellChar = getCellChar(row, col);
		cout << cellChar;

		cout << " ";
	}
	cout << "|" << endl;
}

void Map::placeElements(int elementCount, MapCellType element)
{
	for (int i = 0;i < elementCount;i++) {
		pair<int, int> coordinates = GetRandomAvailableCell();
		board[coordinates.first][coordinates.second] = element;
	}
}

char Map::getCellChar(int row, int column) const
{
	assert(row >= 0 && row < rows);
	assert(column >= 0 && column < columns);

	char result = 0;

	switch (board[row][column])
	{
		case ground:
			result = ' ';
			break;
		case tree:
			result = 'T';
			break;
		case water:
			result = '~';
			break;
		case vampire:
			result = 'V';
			break;
		case werewolf:
			result = 'W';
			break;
		case avatar:
			result = 'A';
			break;
		case potion:
			result = 'P';
			break;
		default:
			assert(false);
			break;
	}

	assert(result != 0);
	return result;
}

bool Map::cellBelowIsAvailable(int row, int column) const
{
	if (row + 1 >= rows) return false;
	assert(column >= 0 && column < columns);

	return (board[row+1][column] == ground);
}

bool Map::cellAboveIsAvailable(int row, int column) const
{
	if (row - 1 < 0) return false;
	assert(columns >= 0 && column < columns);

	return (board[row-1][column] == ground);
}

bool Map::cellLeftIsAvailable(int row, int column) const
{
	if (column - 1 < 0) return false;
	assert(row >= 0 && row < rows);

	return (board[row][column-1] == ground);
}

bool Map::cellRightIsAvailable(int row, int column) const
{
	if (column +1 >= columns) return false;
	assert(row >= 0 && row < rows);

	return board[row][column+1] == ground;
}

bool Map::cellAboveRightIsAvailable(int row, int column) const
{
	if(row<=0 || column >= columns-1) return false;

	return board[row - 1][column + 1] == ground;
}

bool Map::cellAboveLeftIsAvailable(int row, int column) const
{
	if (row <= 0 || column <= 0) return false;

	return board[row-1][column-1]==ground;
}

bool Map::cellBelowRightIsAvailable(int row, int column) const
{
	if (row >= rows - 1 || column >= columns - 1) return false;
	return board[row+1][column+1]==ground;
}

bool Map::cellBelowLeftIsAvailable(int row, int column) const
{
	if (row >= rows - 1 || column <= 0) return false;
	return board[row+1][column-1]==ground;
}

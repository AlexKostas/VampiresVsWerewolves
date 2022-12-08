#include <iostream>
#include <math.h>
#include <cassert>
#include <utility>
#include "Utils.h"
#include "Map.h"
#include "Tree.h"
#include "Ground.h"
#include "WaterCell.h"
#include "Avatar.h"
#include "Werewolf.h"
#include "Vampire.h"
#include "GameEntity.h"

using namespace std;

Map::Map(int x, int y) : werewolvesCount((x * y) / 15), vampiresCount((x * y) / 15) {
	this->rows = x;
	this->columns = y;

	board = new GameEntity** [x];

	for (int i = 0;i < x;i++)
		board[i] = new GameEntity*[y];

	for (int i = 0;i < x;i++)
		for (int j = 0;j < y;j++)
			board[i][j] = NULL;

	populateMap();

	for (int i = 0;i < x;i++)
		for (int j = 0;j < y;j++)
			if(board[i][j] == NULL)
				board[i][j] = new Ground(x, y, this);
}

Map::~Map() {
	for (int i = 0;i < rows;i++)
		delete[] board[i];

	delete[] board;
}

void Map::Update()
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			board[i][j]->update();
	Show();
}

void Map::Show() const {	
	for (int row = 0; row < rows; row++) {
		printBorderRow();
		printCellRow(row);
	}
	printBorderRow();
}

vector<pair<int, int>> Map::GetLegalNeighborCells(int row, int col) const
{
	assert(row >= 0 && row < rows);
	assert(col >= 0 && col < columns);

	vector<pair<int, int>> result;

	if (cellAboveIsAvailable(row, col)) {
		pair<int, int> coords(row + 1, col);
		result.push_back(coords);
	}
	if (cellBelowIsAvailable(row, col)) {
		pair<int, int> coords(row - 1, col);
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

int Map::GetRow() const
{
	return rows;
}

int Map::GetColumn() const
{
	return columns;
}

void Map::populateMap()
{
	int numberOfTrees = round((rows * columns) * (treeDensity / 100.0));
	int numberOfWaterCells = round((rows * columns) * (waterDensity / 100.0));

	//TODO: split into functions

	for (int i = 0;i < numberOfTrees;i++) {
		int x, y;
		do {
			Utils::GetRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != NULL);

		board[x][y] = new Tree(x, y, this);
	}

	for (int i = 0;i < numberOfWaterCells;i++) {
		int x, y;
		do {
			Utils::GetRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != NULL);

		board[x][y] = new WaterCell(x, y, this);
	}

	for (int i = 0;i < vampiresCount;i++) {
		int x, y;
		do {
			Utils::GetRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != NULL);

		Vampire* vampire = new Vampire(x, y, this);
		vampires.push_back(vampire);
		board[x][y] = vampire;
	}

	for (int i = 0;i < werewolvesCount;i++) {
		int x, y;
		do {
			Utils::GetRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != NULL);

		Werewolf* werewolf = new Werewolf(x, y, this);
		werewolves.push_back(werewolf);
		board[x][y] = werewolf;
	}

	int x, y;
	do {
		Utils::GetRandomCoordinates(rows, columns, x, y);
	} while (board[x][y] != NULL);

	board[x][y] = new Avatar(x, y, this);
}

void Map::printBorderRow() const {
	for (int col = 0; col < columns; col++)
		cout << "+" << "===";		

	cout << "+" << endl;
}

void Map::printCellRow(int row) const {
	for (int col = 0; col < columns; col++) {
		cout << "|" << " ";

		board[row][col]->print();

		cout << " ";
	}
	cout << "|" << endl;
}

bool Map::cellAboveIsAvailable(int row, int column) const
{
	if (row + 1 >= rows) return false;
	assert(column >= 0 && column < columns);

	return (board[row+1][column]->IsGround());
}

bool Map::cellBelowIsAvailable(int row, int column) const
{
	if (row - 1 < 0) return false;
	assert(columns >= 0 && column < columns);

	return (board[row-1][column]->IsGround());
}

bool Map::cellLeftIsAvailable(int row, int column) const
{
	if (column - 1 < 0) return false;
	assert(row >= 0 && row < rows);

	return (board[row][column-1]->IsGround());
}

bool Map::cellRightIsAvailable(int row, int column) const
{
	if (column +1 >= columns) return false;
	assert(row >= 0 && row < rows);

	return (board[row][column+1]->IsGround());
} 
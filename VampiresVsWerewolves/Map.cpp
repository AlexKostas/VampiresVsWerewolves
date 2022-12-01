#include <iostream>
#include <math.h>
#include "Utils.h"
#include "Map.h"


using namespace std;

Map::Map( int x,  int y) {
	this->rows = x;
	this->columns = y;

	board = new MapCellType* [x];

	for (int i = 0;i < x;i++) {
		board[i] = new MapCellType[y];
	}

	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			board[i][j] = ground;
		}
	}

	populateMap();
}

Map::~Map() {

	for (int i = 0;i < rows;i++) {
		delete[] board[i];
	}

	delete[] board;
}

void Map::Show() const {	
	for (int row = 0; row < rows; row++) {
		printBorderRow();
		printCellRow(row);
	}
	printBorderRow();
}

void Map::UpdateEntityPosition( int oldRow,  int oldColumn,  int newRow,  int newColumn, MapCellType entity)
{
	board[oldRow][oldColumn] = ground;

	board[newRow][newColumn] = entity;
}

bool Map::IsGroundCell( int row,  int column) const
{
	
	return board[row][column]==ground;
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

	placeElements(numberOfTrees, tree);
	placeElements(numberOfWaterCells, water);
}

void Map::printBorderRow() const {
	for (int col = 0; col < columns; col++) {
		cout << "+" << "===";		
	}
	cout << "+" << endl;
}

void Map::printCellRow(int row) const {
	for (int col = 0; col < columns; col++) {
		cout << "|" << " ";

		switch (board[row][col])
		{
		case ground:
			cout << " ";
			break;
		case tree:
			cout << "T";
			break;
		case water:
			cout << "~";
			break;
		case vampire:
			cout << "V";
			break;
		case werewolf:
			cout << "W";
			break;
		case avatar:
			cout << "A";
			break;
		default:
			//TODO: throw exception
			break;
		}

		cout << " ";
	}
	cout << "|" << endl;
}

void Map::placeElements(int elementCount, MapCellType element)
{
	for (int i = 0;i < elementCount;i++) {
		 int x, y;
		do {
			Utils::GetRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != ground);

		board[x][y] = element;
	}
}
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Map.h"


using namespace std;

Map::Map(unsigned int x, unsigned int y) {
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
			getRandomCoordinates(rows, columns, x, y);
		} while (board[x][y] != ground);

		board[x][y] = element;
	}
}

void Map::getRandomCoordinates(int maxX, int maxY, int& x, int& y)
{
	x = rand() % maxX;
	y = rand() % maxY;
}
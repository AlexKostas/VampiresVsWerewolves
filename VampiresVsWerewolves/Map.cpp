#include <iostream>
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
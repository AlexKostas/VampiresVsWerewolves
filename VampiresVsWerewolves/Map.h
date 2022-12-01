#pragma once


enum MapCellType{ground,tree,water,vampire,werewolf,avatar};

class Map {
public:
	Map(unsigned int rows, unsigned int columns);
	~Map();
	void Show() const;

private:
	const unsigned int treeDensity=5;
	const unsigned int waterDensity = 5;
	unsigned int rows, columns;
	MapCellType** board;       
	void populateMap();
	void printBorderRow() const;
	void printCellRow(int row) const;
	void placeElements(int elementCount, MapCellType element);
	void getRandomCoordinates(int maxX, int maxY, int& x, int& y);
};
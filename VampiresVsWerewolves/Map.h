#pragma once


enum MapCellType{ground,tree,water,vampire,werewolf,avatar};

class Map {
public:
	Map(unsigned int rows, unsigned int columns);
	~Map();
	void Show() const;
	void UpdateEntityPosition(unsigned int oldRow,unsigned int oldColumn,unsigned int newRow,unsigned int newColumn,MapCellType entity);


private:
	const unsigned int treeDensity=5;
	const unsigned int waterDensity =5;
	unsigned int rows, columns;
	MapCellType** board;       
	void populateMap();
	void printBorderRow() const;
	void printCellRow(int row) const;
	void placeElements(int elementCount, MapCellType element);
};
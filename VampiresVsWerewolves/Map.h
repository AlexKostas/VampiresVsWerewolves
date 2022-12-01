#pragma once


enum MapCellType{ground,tree,water,vampire,werewolf,avatar};

class Map {
public:
	Map(unsigned int rows, unsigned int columns);
	~Map();
	void Show() const;





private:
	unsigned int rows, columns;
	MapCellType** board;
	void printBorderRow() const;
	void printCellRow(int row) const;
};

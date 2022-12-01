#pragma once


enum MapCellType{ground,tree,water,vampire,werewolf,avatar};

class Map {
public:
	Map( int rows,  int columns);
	~Map();
	void Show() const;
	void UpdateEntityPosition( int oldRow, int oldColumn, int newRow, int newColumn,MapCellType entity);
	bool IsGroundCell( int row,  int column) const ;
	 int GetRow() const;
	 int GetColumn() const;
private:
	const  int treeDensity=5;
	const  int waterDensity =5;
	 int rows, columns;
	MapCellType** board;       
	void populateMap();
	void printBorderRow() const;
	void printCellRow(int row) const;
	void placeElements(int elementCount, MapCellType element);

};
#pragma once



class GameEntity {
public:
	virtual void update()=0;
	unsigned int getRow() const;
	unsigned int getColumn() const;
	

protected:
	unsigned int row, column;
	unsigned int health, attack, defence;
};


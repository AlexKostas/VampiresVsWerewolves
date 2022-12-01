#pragma once



class GameEntity {
public:
	virtual void update()=0;
	 int getRow() const;
	 int getColumn() const;
	

protected:
	 int row, column;
	 int health, attack, defence;
};


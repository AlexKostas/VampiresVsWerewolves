#pragma once

class GameEntity;

class MapElement {
public:
	MapElement(int row, int column);

	virtual void Print() const = 0;
	void Clear();

	void SetOccupant(GameEntity* occupant);
	GameEntity* GetOccupant() const;

	virtual bool CanBeOccupied() const = 0;

	void PlacePotion();
	void RemovePotion();
	bool HasPotion() const;

	int GetRow() const;
	int GetColumn() const;

protected:
	int row, column;
	GameEntity* occupant;
	bool hasPotion = false;

	bool isOccupied() const;
};
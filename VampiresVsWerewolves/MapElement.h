#pragma once

class GameEntity;

class MapElement {
public:
	virtual void Print() const = 0;
	void Clear();

	void SetOccupant(GameEntity* occupant);
	GameEntity* GetOccupant() const;

	virtual bool CanBeOccupied() const = 0;

	void PlacePotion();
	void RemovePotion();
	bool HasPotion() const;
protected:
	GameEntity* occupant;
	bool hasPotion = false;

	bool isOccupied() const;
};
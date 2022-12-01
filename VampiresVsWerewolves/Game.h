#pragma once
#include <vector>
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"


using namespace std;

class Game {
public:
	Game(int row, int column);
	~Game();
	void Update();


private:
	const  int werewolvesCount;
	const  int vampiresCount;
	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	Avatar* avatar;
	
	void getValidRandomCoordinates( int& row,  int& column);
};
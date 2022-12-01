#pragma once
#include <vector>
#include "Map.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Avatar.h"


using namespace std;

class Game {
public:
	Game(unsigned int row,unsigned column);
	~Game();
	void Update();


private:
	const unsigned int werewolvesCount;
	const unsigned int vampiresCount;

	Map* map;
	vector<Werewolf*> werewolves;
	vector<Vampire*> vampires;
	Avatar avatar;
};
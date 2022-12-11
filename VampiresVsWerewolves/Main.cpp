#include <iostream>
#include <cassert>
#include <limits>
#include "Game.h"
#include "Utils.h"

using namespace std;

void initializeGame(Game*& game);

int main()
{	
	Game* game = NULL;
	initializeGame(game);
	assert(game != NULL);
	
	//srand(time(nullptr));
	game->Run();
	delete game;
}

void initializeGame(Game*& game) {
	do {
		cout << "Give row!" << endl;
		int row = Utils::ReadIntegerFromInput();

		cout << "Give column!" << endl;
		int column = Utils::ReadIntegerFromInput();

		try {
			game = new Game(row, column);
			break;
		}
		catch (invalid_argument) {
			cout << "Invalid board size. Try again..." << endl;
		}
		catch (...) {
			cout << "An error occured. Please try again" << endl;
		}
	} while (true);
}
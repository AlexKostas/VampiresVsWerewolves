#include <iostream>
#include <cassert>
#include "Game.h"

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
		cout << "Give row and column" << endl;
		int row, column;
		cin >> row >> column;
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
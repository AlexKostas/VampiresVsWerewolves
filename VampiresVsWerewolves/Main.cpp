#include <iostream>
#include <cassert>
#include <ctime>
#include "Game.h"

using namespace std;

void initializeGame(Game*& game);

const int frameRate=2;

int main()
{	
	Game* game = NULL;
	initializeGame(game);
	assert(game != NULL);
	
	float frameTime = (1.0 / frameRate) * CLOCKS_PER_SEC;
	assert(frameTime >= 0);

	while (!game->IsOver()) {
		clock_t now = clock();
		while (true) 
		{
			while (clock() - now < frameTime);

			now = clock();
			system("cls");
			game->Update();
		}
	}	

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
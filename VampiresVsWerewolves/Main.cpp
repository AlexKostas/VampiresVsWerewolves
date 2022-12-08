#include <iostream>
#include <cassert>
#include <ctime>
#include <conio.h>
#include "Game.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

void initializeGame(Game*& game);

const int frameRate=5;

int main()
{	
	Game* game = NULL;
	initializeGame(game);
	assert(game != NULL);
	
	float frameTime = (1.0 / frameRate) * CLOCKS_PER_SEC;
	assert(frameTime >= 0);

	//srand(time(nullptr));

	clock_t now = clock();
	while (!game->IsOver()) 
	{
		while (clock() - now < frameTime);

		now = clock();
		system("cls");
		game->Update();

		if (!_kbhit()) continue;

		int c;
		switch ((c = _getch())) {

		case KEY_UP:

			cout << endl << "Up" << endl;//key up

			break;

		case KEY_DOWN:

			cout << endl << "Down" << endl; // key down

			break;

		case KEY_LEFT:

			cout << endl << "Left" << endl; // key left

			break;

		case KEY_RIGHT:

			cout << endl << "Right" << endl; // key right

			break;
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
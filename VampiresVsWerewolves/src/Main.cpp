#include <iostream>
#include <cassert>
#include "Game.h"
#include "Utils.h"

using namespace std;

void initializeGame(Game*& game);

int main(void)
{	
	Game* game = nullptr;
	initializeGame(game);
	assert(game != nullptr);
	
	Utils::InitializeRandomNumGenerator();
	game->Run();
	delete game;

	// Wait for user to input something to close window
	cout << "Give an input to close the window!" << endl;
	string s;
	cin >> s;

	return 0;
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
			cout << "An error occured. Please try again" << endl;//if an unknown error occured
		}
	} while (true);
}
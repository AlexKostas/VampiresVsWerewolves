#include <iostream>
#include <ctime>
#include "Game.h"

using namespace std;

const int frameRate=5;

int main()
{	
	//TODO GET DIMENSIONS FROM USER
	Game game(10, 10);
	
	float frameTime = (1.0 / frameRate) * CLOCKS_PER_SEC;


	//TODO WHILE THE GAME IS NOT OVER
	while (true) {

		clock_t now = clock();//this gets the time in sec.
		while (true)
		{
			while (clock() - now < frameTime);
			//call your function
			now = clock();
			system("cls");
			game.Update();
		}
	}
	
}

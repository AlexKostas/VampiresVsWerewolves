#include <iostream>
#include <limits>
#include <cstdlib>
#include <cassert>
#include "Utils.h"

using std::cin;

void Utils::GetRandomCoordinates(int maxX, int maxY, int& x, int& y)
{
	x = rand() % maxX;
	y = rand() % maxY;

	assert(x >= 0 && x <= maxX);
	assert(y >= 0 && y <= maxY);
}

int Utils::GetRandomNumberInRange(int lowBound, int highBound) {
	int range = highBound - lowBound;
	int num = rand() % range + lowBound;

	assert(num >= lowBound);
	assert(num < highBound);

	return num;
}

int Utils::ReadIntegerFromInput()
{
	int number = 0;
	do {
		cin >> number;
		if (cin) break; //exit if read was successful

		//Clear input buffer 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "This is not an integer. Please type number again" << std::endl;
	} while (true);

	return number;
}

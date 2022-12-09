#include <cstdlib>
#include <cassert>
#include "Utils.h"

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

int Utils::ManhattanDistance(int x1, int x2, int y1, int y2)
{
	return abs(x2 - x1) + abs(y2 - y1);
}

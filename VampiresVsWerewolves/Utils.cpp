#include <cstdlib>
#include <cassert>
#include "Utils.h"

void Utils::GetRandomCoordinates(int maxX, int maxY, int& x, int& y)
{
	//TODO: seed 
	x = rand() % maxX;
	y = rand() % maxY;

	assert(x >= 0 && x <= maxX);
	assert(y >= 0 && y <= maxY);
}

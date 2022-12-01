#include <cstdlib>
#include "Utils.h"

void Utils::GetRandomCoordinates(int maxX, int maxY, int& x, int& y)
{
	//TODO: seed 
	x = rand() % maxX;
	y = rand() % maxY;
}

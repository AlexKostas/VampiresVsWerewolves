#pragma once

class Utils {
public:
	static void GetRandomCoordinates(int maxX, int maxY, int& x, int& y);
	static int GetRandomNumberInRange(int lowBound, int highBound);
	static int ManhattanDistance(int x1, int x2, int y1, int y2);
	static int ReadIntegerFromInput();
};

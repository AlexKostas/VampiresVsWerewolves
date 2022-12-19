#pragma once

class Utils {
public:
	static void InitializeRandomNumGenerator();
	static void GetRandomCoordinates(int maxX, int maxY, int& x, int& y);
	static int GetRandomNumberInRange(int lowBound, int highBound);
	static int ReadIntegerFromInput();
};
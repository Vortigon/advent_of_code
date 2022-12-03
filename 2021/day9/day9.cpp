/*--- Day 9: Smoke Basin ---*/

#include <iostream>
#include "HeightMap.h"

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	HeightMap map;
	if (map.getInput(file))
	{
		std::cout << "Risk level: " << map.getRiskLevel() << 
			"\nBasins' max sizes multiplication: " << map.getMaxSizes() << std::endl;
	}
}
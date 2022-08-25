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
		std::cout << "Risk level: " << map.getRiskLevel() << std::endl;
	}
	std::string str1 = "999898934", str2 = "987796899", str3 = "865685578";
}
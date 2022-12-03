#pragma once
#include <fstream>
#include "Basin.h"

class HeightMap
{
public:
	HeightMap();

	bool getInput(std::ifstream& file);

	int getRiskLevel() const { return risk_level; }
	size_t getMaxSizes() const { return max_size[0] * max_size[1] * max_size[2]; }

private:
	void findLowPoints(std::string* first, std::string* second, std::string* third,
		std::vector<Basin>& basins);
	void checkMaxSize(size_t basin_size);

	int risk_level;
	size_t max_size[3];
	std::string str[3];
};
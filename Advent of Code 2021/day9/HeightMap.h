#pragma once
#include <fstream>
#include "Basin.h"

class HeightMap
{
public:
	HeightMap();

	bool getInput(std::ifstream& file);

	int getRiskLevel() const { return risk_level; }
private:
	void findLowPoints(std::string* first, std::string* second, std::string* third,
		std::vector<Basin>& basins);

	void findNew(std::vector<Basin>& basins, const size_t& i, bool& low_point,
		std::string* str1, std::string* str2, size_t& size);

	int risk_level, max_size[3];
	std::string str[3];
};


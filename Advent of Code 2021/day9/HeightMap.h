#pragma once
#include <fstream>
#include "Basin.h"

class HeightMap
{
public:
	HeightMap();

	bool getInput(std::ifstream&);

	int getRiskLevel() const { return risk_level; }
private:
	void findLowPoints(std::string*, std::string*, std::string*,
		std::vector<Basin>&);

	int risk_level, max_size[3];
	std::string str[3];
};
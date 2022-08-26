#pragma once
#include <iostream>
#include <fstream>
#include "BracketStack.h"

class LineParser
{
public:
	LineParser() : sntx_score{ 0 } {}

	bool getInput(std::ifstream& file);

private:
	void parse (std::string& line);
	uint32_t sntx_score;
};
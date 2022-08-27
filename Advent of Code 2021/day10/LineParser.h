#pragma once
#include <iostream>
#include <fstream>
#include "BracketStack.h"

class LineParser
{
public:
	LineParser() : sntx_score{ 0 } {}

	bool getInput(std::ifstream& file);
	uint32_t getScore() { return sntx_score; }
private:
	void parse (std::string& line);
	uint32_t sntx_score;
};
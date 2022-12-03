#pragma once
#include <fstream>
#include <vector>
#include "BracketStack.h"

class LineParser
{
public:
	LineParser() : sntx_score{ 0 }{}

	bool getInput(std::ifstream& file);

	uint32_t getSyntaxScore() 
	{ return sntx_score; }
	uint64_t getAutoScore();
private:
	void parse (std::string& line);
	void insertScore(uint64_t score);

	size_t lines{ 1 };
	uint32_t sntx_score;
	std::vector<uint64_t> auto_score;
};
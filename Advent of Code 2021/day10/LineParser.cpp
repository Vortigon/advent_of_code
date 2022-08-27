#include "LineParser.h"

bool LineParser::getInput(std::ifstream& file)
{
	if (!file.is_open()) { return false; }

	std::string line;

	while (true)
	{
		file >> line;
		if (!line.size()) break;
		parse(line);
		line.clear();
	}
	return true;
}

void LineParser::parse(std::string& line)
{	size_t size{ line.size() };
	BracketStack stack{ size };
	for (size_t i{ 0 }; i < size; i++)
	{
		if (!stack.load(line[i]))
		{
			switch (line[i])
			{
			case ')': {sntx_score += 3; return; }
			case ']': {sntx_score += 57; return; }
			case '}': {sntx_score += 1197; return; }
			case '>': {sntx_score += 25137; return; }
			}
		}
	}
}
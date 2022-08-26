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
}

void LineParser::parse(std::string& line)
{
	size_t size{ line.size() };
	size_t bracket[4] { 0 };
	for (size_t i{ 0 }; i < size; i++)
	{

	}
}
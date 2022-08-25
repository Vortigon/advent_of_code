#include "HeightMap.h"

HeightMap::HeightMap() : risk_level{ 0 }, max_size{ 0 } {}

bool HeightMap::getInput(std::ifstream& file)
{
	if (!file.is_open()) { return false; }

	int i{ -1 };
	std::vector<Basin> basins;

	while (i != -2)
	{
		switch (i)
		{
		case 0:
		{
			file >> str[i];
			if (file.peek() == EOF)
			{
				findLowPoints(str + 1, str + 2, nullptr, basins);
				i = -2;
			}
			else
			{
				findLowPoints(str + 1, str + 2, str, basins);
				i = 1;
			}
			break;
		}
		case 1:
		{
			file >> str[i];
			if (file.peek() == EOF)
			{
				findLowPoints(str + 2, str, nullptr, basins);
				i = -2;
			}
			else
			{
				findLowPoints(str + 2, str, str + 1, basins);
				i = 2;
			}
			break;
		}
		case 2:
		{
			file >> str[i];
			if (file.peek() == EOF)
			{
				findLowPoints(str, str + 1, nullptr, basins);
				i = -2;
			}
			else
			{
				findLowPoints(str, str + 1, str + 2, basins);
				i = 0;
			}
			break;
		}
		case -1:
		{
			file >> str[0] >> str[1];
			findLowPoints(nullptr, str, str + 1, basins);
			i = 2;
			break;
		}
		}
	}

	return true;
}

void HeightMap::findLowPoints(std::string* first, std::string* second, std::string* third,
	std::vector<Basin>& basins)
{
	size_t size = second->size();

	for (size_t i = 0; i < size; i++)
	{
		char height = (*second)[i];
		if (
			((first && (height < (*first)[i])) || !first) &&
			((third && (height < (*third)[i])) || !third) &&
			((i > 0) && (height < (*second)[i - 1]) || i == 0) &&
			((i < size - 1) && (height < (*second)[i + 1]) || i == size - 1)
			)
		{ risk_level += 1 + height - '0';	}
	}
}
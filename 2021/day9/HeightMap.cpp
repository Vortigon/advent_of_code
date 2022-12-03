#include "HeightMap.h"

HeightMap::HeightMap() : risk_level{ 0 }, max_size{ 0 } {}

bool HeightMap::getInput(std::ifstream& file)
{
	if (!file.is_open()) { return false; }

	char i{ -1 };
	std::vector<Basin> basins;

	while (i != -2)
	{
		if (i != -1) { file >> str[i]; }
		switch (i)
		{
		case 0:
		{
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

	Basin::findNewBasins(*second, third, basins);

	size_t basins_amount{ basins.size() };
	if (third)
	{
		
		for (size_t i{ 0 }; i < basins_amount; i++)
		{
			Basin& returned{ basins[i].continueBasin(*second, *third, basins) };

			size_t ledge_size{basins[i].getLedgeSize()};

			if (!ledge_size || (&basins[i] != &returned))
			{
				if (!ledge_size) { checkMaxSize(basins[i].getSize()); }
				basins.erase(basins.begin() + i);
				basins_amount--;
				i--;
			}
		}
	}
	else
	{
		for (size_t i{ 0 }; i < basins_amount; i++)
		{
			checkMaxSize(basins[i].getSize());
			basins.erase(basins.begin() + i);
			basins_amount--;
			i--;
		}
	}
}

void HeightMap::checkMaxSize(size_t basin_size)
{
	size_t tmp;
	if (basin_size > max_size[0]) { max_size[0] = basin_size; }

	if (max_size[0] > max_size[1])
	{
		tmp = max_size[1];
		max_size[1] = max_size[0];
		max_size[0] = tmp;
	}

	if (max_size[1] > max_size[2])
	{
		tmp = max_size[2];
		max_size[2] = max_size[1];
		max_size[1] = tmp;
	}
}
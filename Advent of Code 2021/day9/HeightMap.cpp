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
		bool low_point{ false };
		char height = (*second)[i];
		if (
			((first && (height < (*first)[i])) || !first) &&
			((third && (height < (*third)[i])) || !third) &&
			((i > 0) && (height < (*second)[i - 1]) || i == 0) &&
			((i < size - 1) && (height < (*second)[i + 1]) || i == size - 1)
			)
		{
			risk_level += 1 + height - '0';
			low_point = true;
		}
		if (first)
		{
			if (third)
			{
				//search for continue of basins in (*third)[i]
			}

			//deleting not connected basins that haven't possible connections


		}
		//seacrhing for new basins
	}
}

void HeightMap::findNew(std::vector<Basin>& basins, const size_t& i, bool& low_point,
	std::string* str1, std::string* str2, size_t& size)
{
	if ((*str1)[i] == '9') { return; }

	//in this context true means that we can use index to create new basin
	// so no basin includes that index and string has that index
	bool l_index_free{ i == 0 ? false : true }, r_index_free{ i == size - 1 ? false : true };

	if (l_index_free && (*str1)[i - 1] == '9') { l_index_free = false; }
	if (r_index_free && (*str1)[i - 1] == '9') { l_index_free = false; }

	for (Basin& basin : basins)
	{
		if (basin.hasLedge(i)) return;

		//if there's no previous basins that include indexes in left and right of i
		//then we check if current basin includes them
		if (l_index_free) { l_index_free = !basin.hasLedge(i - 1); }
		if (r_index_free) { r_index_free = !basin.hasLedge(i + 1); }
	}

	//if no basin includes i-index then we possibly found new basin
	//its start size is 1 because it includes  i-index already
	size_t new_basin_size{ 1 };
	//if "it's possible to include left of i index to new basin"
	//and their heights differ (so one of them is smaller)
	if (l_index_free && ((*str1)[i - 1] != (*str)[i]))
	{
		new_basin_size++;
	}
}
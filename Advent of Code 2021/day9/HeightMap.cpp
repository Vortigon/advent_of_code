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
			//maybe i should make local vector of LP indexes 
			// so it will allow to check connecting of basins later
			//for example in new basin r_index doesn't have information is it LP or not
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
	std::string& mid_str, std::string* third, size_t& size)
{
	if (mid_str[i] == '9') { return; }

	//in this context true means that we can use index to create new basin
	// so no basin includes that index and string has that index
	bool l_index_free{ i == 0 ? false : true }, r_index_free{ i == size - 1 ? false : true };

	//does it even make sense to check left?
	//like, it litterally goes from left side to right
	//i guess i'll keep it until tests
	if (l_index_free && mid_str[i - 1] == '9') { l_index_free = false; }
	if (r_index_free && mid_str[i - 1] == '9') { l_index_free = false; }

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

	//if "it's possible to include left/right of i index to new basin"
	if (l_index_free) { new_basin_size++; }
	if (r_index_free) { new_basin_size++; }

	if (new_basin_size > 1)
	{
		Basin new_basin(new_basin_size, low_point);

		if (l_index_free) { new_basin.addLedge(i - 1); }
		new_basin.addLedge(i);
		if (r_index_free) { new_basin.addLedge(i + 1); }

		basins.push_back(new_basin);
	}

	//if there's no horizontal expandings maybe basin has vertical continue like
	// 999
	// 989		<- mid_str is here 
	// 979		<- third is here
	// 969
	//so there we should check third line for it
	//else we just expanding it in second line and then continuing in third like usual basin
}
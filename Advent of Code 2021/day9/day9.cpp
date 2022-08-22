/*--- Day 9: Smoke Basin ---*/

#include <fstream>
#include <iostream>

class HeightMap
{
public:
	HeightMap() : risk_level{ 0 } {}

	bool getInput(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }

		int i{ -1 };
		while (i != -2)
		{
			switch (i)
			{
			case 0: 
			{
				file >> str[i];
				if (file.peek() == EOF)
				{
					findLowPoints(str + 1, str + 2, nullptr);
					i = -2;
				}
				else
				{
					findLowPoints(str + 1, str + 2, str);
					i = 1;
				}
				break;
			}
			case 1:
			{
				file >> str[i];
				if (file.peek() == EOF)
				{
					findLowPoints(str + 2, str, nullptr);
					i = -2;
				}
				else
				{
					findLowPoints(str + 2, str, str + 1);
					i = 2;
				}
				break;
			}
			case 2:
			{
				file >> str[i];
				if (file.peek() == EOF)
				{
					findLowPoints(str, str + 1, nullptr);
					i = -2;
				}
				else
				{
					findLowPoints(str, str + 1, str + 2); 
					i = 0;
				}
				break;
			}
			case -1:
			{
				file >> str[0] >> str[1];
				findLowPoints(nullptr, str, str + 1);
				i = 2;
				break;
			}
			}
		}

		return true;
	}

	int getRiskLevel() const { return risk_level; }
private:
	void findLowPoints(std::string* first, std::string* second, std::string* third)
	{
		size_t size = second->size();

		for (size_t i = 0; i < size; i++)
		{
			char height = (*second)[i];
			if (
				( (first && ( height < (*first)[i] ) ) || !first) &&
				( (third && ( height < (*third)[i] ) ) || !third) &&
				( (i > 0) && ( height < (*second)[i-1] ) || i == 0) &&
				( (i < size - 1 ) && ( height < (*second)[i+1] ) || i == size - 1)
				)
			{
				risk_level += 1 + height - '0';
			}
		}
	}
	int risk_level;
	std::string str[3];
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	HeightMap map;
	if (map.getInput(file))
	{
		std::cout << "Risk level: " << map.getRiskLevel() << std::endl;
	}
}
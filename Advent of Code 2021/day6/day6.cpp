/*--- Day 6: Lanternfish ---*/

#include <iostream>
#include <fstream>

class Fish
{
public:
	Fish()
		: amount{ 0 } {}

	bool init(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }

		while (file.peek() != EOF)
		{
			int buf;
			file >> buf;
			amount[buf]++;
			file.get();
		}
		return true;
	}

	uint64_t getSum() const
	{
		uint64_t sum{ 0 };
		for (uint8_t i = 0; i < 9; i++)
		{
			sum += amount[i];
		}
		return sum;
	}

	void simulate(uint16_t days)
	{
		for (uint16_t i = 0; i < days; i++)
		{
			uint64_t temp = amount[0];
			for (uint16_t j = 0; j < 8; j++)
			{
				amount[j] = amount[j + 1];
			}
			amount[6] += temp;
			amount[8] = temp;
		}
	}
private:
	uint64_t amount[9];
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	Fish fish;
	if (fish.init(file))
	{
		fish.simulate(80);
		std::cout << "80 days: " << fish.getSum();
		fish.simulate(256 - 80);
		std::cout << "\n256 days: " << fish.getSum();
	}
	file.close();
}

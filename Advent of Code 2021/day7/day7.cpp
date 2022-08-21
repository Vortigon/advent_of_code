/*--- Day 7: The Treachery of Whales ---*/

#include <iostream>
#include <fstream>
#include <vector>

class Crab
{
public:
	Crab()
		: minus{ 0 }, plus{ 0 }, final_pos{ 0 }, zeros{ 0 }, arith_mean{ 0 } {}

	~Crab() { crab_pos.~vector(); }

	bool loadCrabs(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }

		while (1)
		{
			int new_num;
			file >> new_num;
			crab_pos.push_back(new_num);
			arith_mean += new_num;

			new_num -= final_pos;

			handleDistance(new_num);

			if (new_num) { shift(); }

			if (file.get() == '\n') { break; }
		}
		crab_pos.shrink_to_fit();
		arith_mean /= crab_pos.size();

		return true;
	}

	uint64_t getFuelConsumption() const
	{
		uint64_t fuel{ 0 };
		for (const int& i : crab_pos)
		{
			int distance = i - final_pos;
			fuel += distance < 0 ? -distance : distance;
		}
		return fuel;
	}

	//Probably that's more menthaGlacier's engineering that crabs'
	uint64_t getCrabEnginFuelConsum() const
	{
		uint64_t fuel{ 0 };

		for (const int& i : crab_pos)
		{
			int distance = i - arith_mean;
			if (distance < 0) { distance *= -1; }
			fuel += (1 + distance) * distance / 2;
		}
		return fuel;
	}

private:

	void handleDistance(int distance)
	{
		if (distance == 0)
		{
			zeros++;
			return;
		}

		if (distance > 0)
		{
			if (plus.amount == 0 ||
				(distance < plus.min_from_zero))
			{
				plus.min_from_zero = distance;
			}
			plus.amount++;
		}
		else
		{
			distance *= -1;
			if (minus.amount == 0 ||
				(distance < minus.min_from_zero))
			{
				minus.min_from_zero = distance;
			}
			minus.amount++;
		}
	}

	void shift()
	{
		if (plus.amount > zeros + minus.amount)
		{
			final_pos += plus.min_from_zero;
			refresh();
			return;
		}
		if (minus.amount > zeros + plus.amount)
		{
			final_pos -= minus.min_from_zero;
			refresh();
			return;
		}
	}

	void refresh()
	{
		plus.amount = 0;
		minus.amount = 0;
		zeros = 0;

		for (const int& i : crab_pos)
		{ handleDistance(i - final_pos); }
	}

	struct
	{
		int amount, min_from_zero;
	} minus, plus;
	int final_pos, zeros, arith_mean;
	std::vector<int> crab_pos;
};

int main()
{
	std::ifstream file("input.txt");

	Crab crab;
	if (crab.loadCrabs(file))
	{
		std::cout << "Part1: " << crab.getFuelConsumption() <<
			"\nPart2: " << crab.getCrabEnginFuelConsum() << std::endl;
	}
}
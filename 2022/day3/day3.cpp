#include <iostream>
#include <fstream>
#include <string>

size_t getLetterIndex(char letter)
{
	const char letters[] =
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (size_t i = 0; i < sizeof(letters); i++)
	{
		if (letter == letters[i]) { return i; }
	}
	return sizeof(letters);
}

class Reorganizer
{
public:
	Reorganizer() : priority_sum(0) {}

	int operator()(std::ifstream& file)
	{
		if (!file.is_open()) { return 1; }

		std::string rucksack;
		while(getline(file, rucksack))
		{
			bool has_item[52] = {false};
			size_t length = rucksack.size();

			for(size_t i = 0; i < length/2; i++)
			{
				has_item[getLetterIndex(rucksack[i])] = true;
			}

			for(size_t i = length/2; i < length; i++)
			{
				size_t index = getLetterIndex(rucksack[i]);
				if (has_item[index])
				{
					priority_sum += index+1;
					has_item[index] = false;
				}
			}
		}
		return 0;
	}

	size_t getPrioritySum() { return priority_sum; }
private:
	size_t priority_sum;
};

class GroupFinder
{
public:
	GroupFinder() : priority_sum(0) {}

	int operator()(std::ifstream& file)
	{
		if (!file.is_open()) { return 1; }
		
		std::string rucksack;
		uint8_t has_item[52] = {0};
		while(getline(file, rucksack))
		{
			bool has_on_line[52] = {false};
			size_t length = rucksack.size();
			for(size_t i = 0; i < length; i++)
			{
				size_t index = getLetterIndex(rucksack[i]);
				if (!has_on_line[index])
				{
					has_on_line[index] = true;
					if(++has_item[index] == 3)
					{
						priority_sum += index+1;
						for(uint8_t& j : has_item) { j = 0; }
						break;
					}
				}
			}
		}
		return 0;
	}

	size_t getPrioritySum() { return priority_sum; }
private:
	size_t priority_sum;
};

int main()
{
	std::ifstream fs("input.txt");
	Reorganizer reorg;

	if (reorg(fs)) { exit(1); }
	std::cout << "Priority sum: " << reorg.getPrioritySum() << std::endl;

	fs.close();
	fs.open("input.txt");
	GroupFinder finder;

	if (finder(fs)) { exit(2); }
	std::cout << "Group priority sum: " << finder.getPrioritySum() << std::endl;

	fs.close();
	return 0;
}

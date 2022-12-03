#include <iostream>
#include <fstream>

int main()
{
	std::fstream fs("input.txt");
	if (!fs.is_open()) { exit(1); }

	uint64_t max_calories[3] = {0};
	uint64_t current_sum{0}, current;

	while(fs >> current)
	{
		current_sum += current;
		fs.get();

		if (fs.peek() == '\n')
		{
			for (int i = 0; i < 3; i++)
			{
				if (max_calories[i] <= current_sum)
				{
					uint64_t temp = max_calories[i];
					max_calories[i] = current_sum;
					current_sum = temp;
				}
			}

			current_sum = 0;
		}
		current = 0;
	}

	current_sum = 0;
	std::cout << "Max values:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		current_sum += max_calories[i];
		std::cout << '[' << i+1 << "]:" << max_calories[i] << std::endl;
	}
	std::cout << "Their sum is " << current_sum << std::endl;
	return 0;
}

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(1); }

	std::vector<std::deque<char>> crates9000, crates9001;
	std::string buffer;

	while(getline(file, buffer))
	{
		size_t position = buffer.find('[');
		if (position == std::string::npos)
		{
			file.get();
			break;
		}

		while (position != std::string::npos)
		{
			size_t size = crates9000.size();
			if (position/4 >= size)
			{
				for (size_t i = 0; i < (position/4 + 1) - size; i++)
				{
					std::deque<char> placeholder;
					crates9000.push_back(placeholder);
					crates9001.push_back(placeholder);
				}
			}
			crates9000[position/4].push_back(buffer[position+1]);
			crates9001[position/4].push_back(buffer[position+1]);

			position = buffer.find('[', position+4);
		}
	}

	while(getline(file, buffer))
	{
		size_t operation[3] = {0}, offset = 0;
		for (size_t j = 0; j < 3; j++)
		{
			size_t pos = buffer.find(' ', offset) + 1;
			while(buffer[pos] != ' ' && pos < buffer.size())
			{
				operation[j] = operation[j] * 10 + (buffer[pos++] - '0');
			}
			offset = ++pos;
		}

		std::deque<char> crate_pack;
		for (size_t i = 0; i < operation[0]; i++)
		{
			crates9000[operation[2]-1].push_front(crates9000[operation[1]-1].front());
			crates9000[operation[1]-1].pop_front();

			crate_pack.push_back(crates9001[operation[1]-1].front());
			crates9001[operation[1]-1].pop_front();
		}

		while(!crate_pack.empty())
		{
			crates9001[operation[2]-1].push_front(crate_pack.back());
			crate_pack.pop_back();
		}
	}
	
	std::cout << "Top crates, moved by CrateMover9000:" << std::endl;
	for (auto& i : crates9000)
	{
		std::cout << i.front();
	}
	std::cout << std::endl;

	std::cout << "Top crates, moved by CrateMover9001:" << std::endl;
	for (auto& i : crates9001)
	{
		std::cout << i.front();
	}
	std::cout << std::endl;
	return 0;
}

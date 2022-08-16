/*--- Day 1: Sonar Sweep ---*/
/*Input file name is "input.txt", it is located in the same folder as day1.cpp*/

#include <fstream>
#include <iostream>

class Conveyor
{
public:
	enum class Exception
	{
		FILE_NOT_OPEN = -2,
		NOT_ENOUGH_VALUES = -3
	};

	Conveyor(std::string file_name)	
		: file(file_name), depth{ -1, -1, -1, -1 }, increases { 0 } 
	{
		if (!file.is_open())
		{throw Exception::FILE_NOT_OPEN;}

		for (int i = 0; i < 4; i++)
		{
			file >> depth[i];
			if (file.peek() == EOF)
			{throw Exception::NOT_ENOUGH_VALUES;}
		}
	}

	~Conveyor() { file.close(); }
	
	bool next()
	{
		if (depth[0] < depth[3])
			{increases++;}

		depth[0] = depth[1];
		depth[1] = depth[2];
		depth[2] = depth[3];

		file >> depth[3];
		if (file.peek() == EOF)
			return false;

		return true;
	}

	unsigned int getIncreases() { return increases; }

private:
	Conveyor();

private:
	std::ifstream file;
	int depth[4];
	unsigned int increases;
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) exit(-2);
	if (file.eof()) exit(-3);

	int depth, prev_depth{ 0 };
	file >> depth;

	unsigned int increases{ 0 };

	while (1)
	{
		prev_depth = depth;
		file >> depth;

		if (file.peek() == EOF)
		{
			file.close();
			break;
		}
		if (depth > prev_depth) increases++;
	}
	std::cout << "Increases: " << increases << std::endl;

	try
	{
		Conveyor depths("input.txt");
		while (depths.next()) ;

		std::cout << "Increases part two: " << depths.getIncreases() << std::endl;
	}
	catch (Conveyor::Exception code)
	{
		switch (code)
		{
			case Conveyor::Exception::FILE_NOT_OPEN:
			{
				std::cout << "Failed to open file \"input.txt\"." << std::endl;
				exit(-2);
			}
			case Conveyor::Exception::NOT_ENOUGH_VALUES:
			{
				std::cout << "There must be 4 or more values for part two solution." << std::endl;
				exit(-3);
			}
		}
	}
	catch (...) { std::cout << "Unexpected error." << std::endl; exit(-10); }
}
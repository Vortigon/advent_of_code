/*--- Day 2: Dive! ---*/
/*Input file name is "input.txt", it is located in the same folder as day1.cpp*/

#include <iostream>
#include <fstream>
#include <string>

class Submarine
{
public:
	enum class Part
	{
		one = 1,
		two = 2
	};

	Submarine()
		: part{Part::one}, value {	0 }, x{ 0 }, y{ 0 }, aim{ 0 }
	{}
	
	bool recieveCommand(std::ifstream& file)
	{
		if (!file.is_open())
			return false;

		file >> command >> value;
		if (file.peek() == EOF) 
			return false;
		
		handleCommand();
		return true;
	}

	int getAnswer() { return x * y; }

	void changeTaskPart(Part p)
	{
		part = p;
		x = 0;
		y = 0;
		aim = 0;
	}

private:

	void handleCommand()
	{
		switch (part)
		{
			case Part::one:
			{
				if (command == "up") y -= value;
				if (command == "down") y += value;
				if (command == "forward") x += value;
				break;
			}
			case Part::two:
			{
				if (command == "up")	 aim -= value;
				if (command == "down") aim += value;
				if (command == "forward")
				{
					x += value;
					y += value * aim;
				}
				break;
			}
		}
		command.clear();
	}

	Part part;
	int value;
	int x, y, aim;
	std::string command;
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) exit(-2);

	Submarine boat;

	while (boat.recieveCommand(file)) {}

	std::cout << "Answer part 1: " << boat.getAnswer() << std::endl;
	file.close();

	boat.changeTaskPart(Submarine::Part::two);

	file.open("input.txt");
	if (!file.is_open()) exit(-2);

	while (boat.recieveCommand(file)) {}

	std::cout << "Answer part 2: " << boat.getAnswer() << std::endl;
	file.close();
}
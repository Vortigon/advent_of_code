/*--- Day 8: Seven Segment Search ---*/

#include <iostream>
#include <fstream>

class Digits
{
public:
	Digits()
		: uniq_digits{ 0 } {}

	bool getInput(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }
		
		while (1)
		{
			file.ignore(100, '|');

			if (file.peek() == EOF) { break; }

			for (int i = 0; i < 4; i++)
			{
				std::string buf;
				file >> buf;

				size_t size = buf.size();
				switch (size)
				{
				case 2:
				case 3:
				case 4:
				case 7:
				{uniq_digits++; }
				default: { break; }
				}
				buf.clear();
			}
		}
	}

	size_t getUniqDigits() const { return uniq_digits; }
private:
	size_t uniq_digits;
};

int main()
{
	std::ifstream file("input.txt");
	Digits digits;
	if (digits.getInput(file))
	{
		std::cout << "Unique Digits (1, 4, 7, 8): " << digits.getUniqDigits();
	}
}

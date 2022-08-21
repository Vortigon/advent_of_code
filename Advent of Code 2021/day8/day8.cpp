/*--- Day 8: Seven Segment Search ---*/

#include <iostream>
#include "Digits.h"

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	Digits digits;
	if (digits.getInput(file))
	{
		std::cout << "Unique Digits (1, 4, 7, 8): " << digits.getUniqDigits() <<
			"\nOutput values sum: " << digits.getSum() << std::endl;
	}
}
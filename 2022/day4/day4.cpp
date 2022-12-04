#include <iostream>
#include <fstream>
#include <utility>
#include <set>

int main()
{
	std::ifstream fs("input.txt");
	if (!fs.is_open()) { exit(1); }

	size_t fully_contain = 0, overlaped = 0;
	std::pair<size_t, size_t> left{0,0}, right{0,0};
	while(fs >> left.first)
	{
		char delim = fs.get();
		fs >> left.second;

		delim = fs.get();
		fs >> right.first;

		delim = fs.get();
		fs >> right.second;

		if ((left.first <= right.first && left.second >= right.second)
		|| (right.first <= left.first && right.second >= left.second))
		{ fully_contain++; }

		if ((right.first <= left.first && left.first <= right.second)
		|| (right.first <= left.second && left.second <= right.second)
		|| (left.first <= right.first && right.first <= left.second)
		|| (left.first <= right.second && right.second <= left.second))
		{ overlaped++; }
	}

	std::cout << "Fully contained: " << fully_contain <<
		"\nTotal overlaped: " << overlaped << std::endl;
	return 0;
}

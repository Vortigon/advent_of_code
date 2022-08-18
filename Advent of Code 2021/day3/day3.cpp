/*--- Day 3: Binary Diagnostic ---*/
#include "Diagnostic.h"

int main()
{	
	std::ifstream file{ "input.txt" };
	if (!file.is_open()) { exit(-2); }

	Diagnostic tool;
	while (1)
	{
		int err_code{ tool.insertLine(file) };
		
		switch (err_code)
		{
		case 0: { continue; }
		case -1: 
		{
			std::cout << "Power consumption: " << tool.getPowerConsumption() <<
				"\nLife support rating: " << tool.getLifeSupportRating() << std::endl;
			break; 
		}
		case -2: { std::cout << "Failed to open file\n"; break; }
		case -3: { std::cout << "Failed to allocate memory\n"; break; }
		}
		break;
	}
}

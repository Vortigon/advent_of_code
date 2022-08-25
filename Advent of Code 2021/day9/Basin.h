#pragma once
#include <iostream>
#include <vector>

class Basin
{
public:
	Basin();
	Basin(size_t);

	static void findNewBasins(std::string&, std::string*, std::vector<Basin>&);

	void addLedge(size_t);
	bool hasLedge(size_t) const;
	//Basin& expandNew(std::string&, std::vector<Basin>&);
	Basin& continueBasin(std::string&, std::string&, std::vector<Basin>&);
	void expandBasin(std::string&, size_t remain = 0);
private:
	size_t size;
	std::vector<size_t> ledge;
};
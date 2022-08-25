#pragma once
#include <iostream>
#include <vector>

class Basin
{
public:
	Basin();
	Basin(size_t, bool);

	Basin& operator+=(Basin&);
	void addLedge(size_t);
	bool hasLedge(size_t) const;
	Basin& expandNew(std::string&, std::vector<Basin>&);
	Basin& continueBasin(std::string&, std::string&, std::vector<Basin>&, size_t&);
	void expandBasin(std::string&);
private:
	size_t size;
	bool connected;
	std::vector<size_t> ledge;
};
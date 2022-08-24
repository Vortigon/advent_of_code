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
	Basin* expandNew(std::string&, std::vector<Basin>&);
private:
	size_t size;
	bool connected;
	std::vector<size_t> ledge;
};

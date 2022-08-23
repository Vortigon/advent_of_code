#pragma once
#include <vector>

class Basin
{
public:
	Basin();

	Basin& operator+=(Basin& basin);
	
	bool hasLedge(size_t i) const;//&?
	
private:
	size_t size;
	bool connected;
	std::vector<size_t> ledge;
};


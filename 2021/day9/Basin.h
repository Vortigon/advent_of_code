#pragma once
#include <iostream>
#include <vector>

class Basin
{
public:
	Basin();
	Basin(size_t);

	static void findNewBasins(std::string& second, std::string* third, std::vector<Basin>& basins);

	void addLedge(size_t new_ledge);
	bool hasLedge(size_t i) const;

	size_t getLedgeSize() const { return ledge.size(); }
	size_t getSize() const { return size; }

	Basin& continueBasin(std::string& from_str, std::string& to_str, std::vector<Basin>& basins);
	void expandBasin(std::string& basin_str, size_t remain = 0);

private:
	size_t size;
	std::vector<size_t> ledge;
};
#include "Basin.h"

Basin::Basin() : size{ 0 }, connected{ false } {}

Basin::Basin(size_t _s, bool _c) : size{ _s }, connected{ _c } {}

Basin& Basin::operator+=(Basin& basin)
{
	size += basin.size;
	connected |= basin.connected;
	for (const size_t& i : basin.ledge)
	{
		ledge.push_back(i);
	}
	return *this;
}

bool Basin::hasLedge(size_t i) const
{
	int ledge_size = ledge.size();
	for (int j = 0; j < ledge_size; j++)
	{
		if (i == ledge[j]) return true;
	}
	return false;
}

void Basin::addLedge(size_t new_ledge)
{
	ledge.push_back(new_ledge);
	//TODO?
	//make ledge sorted, so it'll be possible to do easier checks in expanding
}

Basin* Basin::expandNew(std::string& mid_str, std::vector<Basin>& basins)
{
	while (ledge[0] > 0)
	{
		if (mid_str[ledge[0] - 1] == '9') { break; }
		//there should be checking if some basin has ledge[0] - 1
		// so if yes, we unite two basins 
		//and else we just inserting new index to that basin
		bool from_other_basin = false;
		for (Basin& basin : basins)
		{
			if (&basin == this) { continue; }
			if (basin.hasLedge(ledge[0] - 1))
			{
				from_other_basin = true;	//we should check right after i guess
				//smth like basin += *this and then return &basin
				// out of method we check new basin adress with returned
				//and if it changed then we deleting new basin
				break;
			}
		}
		if (!from_other_basin)
		{
			ledge.insert(ledge.begin(), ledge[0] - 1);
		}
	}
}
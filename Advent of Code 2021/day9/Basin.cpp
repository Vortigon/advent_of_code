#include "Basin.h"

Basin::Basin() : size{ 0 }, connected{ false } {}

Basin::Basin(size_t _s, bool _c) : size{ _s }, connected{ _c } {}

Basin& Basin::operator+=(Basin& basin)
{
	size += basin.size;
	connected |= basin.connected;
	for (const size_t& i : basin.ledge)
	{
		addLedge(i);
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
	size_t ledge_size{ ledge.size() };
	std::vector<size_t>::iterator place{ ledge.begin() };

	for (size_t i = 0; i < ledge_size; i++)
	{
		if (new_ledge == ledge[i]) { return; }
		if (new_ledge < ledge[i]) 
		{
			ledge.insert(ledge.begin() + i, new_ledge);
			return;
		}
	}
	ledge.push_back(new_ledge);
}

Basin& Basin::expandNew(std::string& mid_str, std::vector<Basin>& basins)
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

	return *this;//indev placeholder
}

Basin& Basin::continueBasin(std::string& from_str, std::string& to_str, std::vector<Basin>& basins, size_t& remain)
{
	//expanding basin to next str
	size_t ledge_size{ ledge.size() };
	remain = ledge_size;
	bool check_other_basin{ true };	//checking once because of input
	
	for (size_t i{ 0 }; i < ledge_size;)
	{
		if (to_str[ledge[i]] == '9')
		{
			ledge.erase(ledge.begin() + i);
			ledge_size--;
			remain--;
			check_other_basin = false;	//input issue
		}
		else 
		{
			for (Basin& basin : basins)
			{
				if (&basin == this || !check_other_basin) { break; }
				if (basin.hasLedge(ledge[i]))
				{
					remain--;
					for (size_t j{ i + 1 }; j < ledge_size; j++)
					{
						if (to_str[ledge[j]] == '9' || basin.hasLedge(ledge[j]))
						{
							remain--;
						}
						else
						{
							size++;
							basin.ledge.push_back(ledge[j]);	//actually should be basin.addLedge(ledge[j]), input issue
						}
					}
					basin.size += size;
					basin.connected |= connected;
					return basin;
				}
			}
			check_other_basin = false;
			i++; size++;
		}
	}

	if (ledge_size > 0) { expandBasin(to_str, basins); }
	return *this;
}

void Basin::expandBasin(std::string& basin_str, std::vector<Basin>& basins)	//REWRITE
{
	////expanding basin in its last str
	//size_t ledge_size{ ledge.size() };
	//for (size_t i{ 0 }; i < ledge_size;)
	//{
	//	if (i > 0)	//expanding to left
	//	{
	//		for (size_t j{ i - 1 }; j >= 0; j--)
	//		{
	//			if (basin_str[j] == '9') { break; }

	//			for (Basin& basin : basins)
	//			{
	//				if (basin.hasLedge(j))
	//				{

	//				}
	//			}

	//			size++;
	//			addLedge(j);
	//		}
	//	}
	//}
}
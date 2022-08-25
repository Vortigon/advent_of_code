#include "Basin.h"

Basin::Basin() : size{ 0 } {}

Basin::Basin(size_t _s) : size{ _s } {}

bool Basin::hasLedge(size_t i) const
{
	int ledge_size = ledge.size();
	for (int j = 0; j < ledge_size; j++)
	{
		if (i == ledge[j]) { return true; }
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

void Basin::findNewBasins(std::string& second, std::string* third, std::vector<Basin>& basins)
{
	size_t str_size{ second.size() };
	for (size_t i{ 0 }; i < str_size; i++)
	{
		if (second[i] == '9') { continue; }

		bool left{ (i > 0) && (second[i - 1] != '9') ? true : false },
				right{ (i + 1 < str_size) && (second[i + 1] != '9') ? true : false },
				down{ (third) && ( (*third)[i] != '9') ? true : false};

		if (!left && !right && !down) { continue; }

		bool from_other_basin = false;
		for (Basin& basin : basins)
		{
			if (*(basin.ledge.end() - 1) < i) { continue; }
			if (*(basin.ledge.begin()) > i) { break; }
			if (basin.hasLedge(i)) { from_other_basin = true; break; }
		}
		if (from_other_basin) { continue; }

		Basin new_basin{ 1 };
		new_basin.addLedge(i);
		new_basin.expandBasin(second);

		size_t basins_amount{ basins.size() };
		std::vector<Basin>::iterator place{ basins.begin() };

		for (size_t j = 0; j <= basins_amount; j++)
		{
			if (j == basins_amount) { basins.push_back(new_basin); break; }

			if (*(new_basin.ledge.begin()) < basins[j].ledge[0])
			{
				place += j;
				basins.insert(place, new_basin);
				break;
			}
		}
	}
}

Basin& Basin::continueBasin		//expanding basin to next str
(std::string& from_str, std::string& to_str, std::vector<Basin>& basins)
{
	size_t ledge_size{ ledge.size() }, remain{ ledge_size };
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
					if (remain) { basin.expandBasin(to_str, remain); }
					return basin;
				}
			}
			check_other_basin = false;
			i++; size++;
		}
	}

	if (ledge_size > 0) { expandBasin(to_str); }
	return *this;
}

void Basin::expandBasin(std::string& basin_str, size_t remain) //expanding basin in its last str
{
	size_t ledge_size{ ledge.size() }, str_size{ basin_str.size() };
	for (size_t i{ remain ? ledge_size - remain : 0 }; i < ledge_size; i++)
	{
		for (size_t j{ 1 }; j <= ledge[i]; j++)//expanding to left
		{
			if (basin_str[ledge[i] - j] == '9') { break; }

			size++;
			ledge_size++;
			addLedge(ledge[i] - j);
			i++;
		}

		if (i >= ledge.size())
		{
			int a = 0;
			a++;
		}
		while (ledge[i] < str_size - 1)	//expanding to right
		{
			if (basin_str[ledge[i] + 1] == '9') { break; }

			if ( (i < ledge_size - 1) && (ledge[i] + 1 == ledge[i + 1]) )
			{
				i++;
				if (i >= ledge.size())
				{
					int a = 0;
					a++;
				}
				continue;
			}
			else
			{
				addLedge(ledge[i] + 1);
				size++;
				ledge_size++;
				i++;
				if (i >= ledge.size())
				{
					int a = 0;
					a++;
				}
			}
		}
	}
}
/*"9869998789964334578995937892397654398945689345678979987643012398967898767998776798890234999898957898"*/
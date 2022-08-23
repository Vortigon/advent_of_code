#include "Basin.h"

Basin::Basin() : size{ 0 }, connected{ false } {}

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

bool Basin::hasLedge(size_t i) const//&?
{
	int ledge_size = ledge.size();
	for (int j = 0; j < ledge_size; j++)
	{
		if (i == ledge[j]) return true;
	}
	return false;
}
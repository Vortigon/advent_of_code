#include "Diagnostic.h"

Diagnostic::Diagnostic() : amount{ nullptr }, binTree_root{ true }, length{ 0 } {}
Diagnostic::~Diagnostic() { delete[] amount; binTree_root.deleteTree(); }

int Diagnostic::insertLine(std::ifstream& file)
{
	if (!file.is_open()) { return -2; }

	file >> bincode;

	size_t len = bincode.length();
	if (!len) { return -1; }
	length = len;

	if (!amount)
	{
		if (!allocAmount())
		{
			return -3;
		}
	}

	for (size_t i = 0; i < length; i++)
	{
		if (bincode[i] == '0')
		{
			amount[i].zeros++;
			continue;
		}
		if (bincode[i] == '1')
		{
			amount[i].ones++;
		}
	}
	binTree_root.insertLine(bincode, length);
	bincode.clear();
	return 0;
}

uint32_t Diagnostic::getPowerConsumption() const
{
	uint32_t gamma{ 0 }, epsilon{ 0 };

	for (size_t i = 0; i < length; i++)
	{
		if (amount[i].ones >= amount[i].zeros)
		{
			gamma |= 1 << (length - 1 - i);
		}
		else
		{
			epsilon |= 1 << (length - 1 - i);
		}
	}

	return gamma * epsilon;
}

uint32_t Diagnostic::getLifeSupportRating() const
{
	uint32_t o2{ 0 }, co2{ 0 };
	std::string buffer;

	binTree_root.recursiveSearch(buffer, Tree::SF::SF_ModeO2);
	binToDec(buffer, o2);
	binTree_root.recursiveSearch(buffer, Tree::SF::SF_ModeCO2);
	binToDec(buffer, co2);
	/*1101 1111 0101 =3573*/
	/*"0001 0010 0001 = 289"*/
	return o2 * co2;
}

bool Diagnostic::allocAmount()
{
	if (length > sizeof(uint32_t) * 8) return false;
	amount = new Bin[length];
	if (!amount) return false;

	for (size_t i = 0; i < length; i++)
	{
		amount[i].zeros = 0;
		amount[i].ones = 0;
	}
	return true;
}

void Diagnostic::binToDec(std::string& buffer, uint32_t& value) const
{
	for (size_t i = 0; i < length; i++)
	{
		if (buffer[i] == '1')
		{
			value |= 1 << (length - 1 - i);
		}
	}
	buffer.clear();
}

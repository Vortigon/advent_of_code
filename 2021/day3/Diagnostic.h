#pragma once
#include "Tree.h"
#include <fstream>

class Diagnostic
{
public:
	Diagnostic();
	~Diagnostic();

	int insertLine(std::ifstream&);
	uint32_t getPowerConsumption() const;
	uint32_t getLifeSupportRating() const;
private:
	bool allocAmount();
	void binToDec(std::string&, uint32_t&) const;
private:
	struct Bin 
	{
		uint32_t zeros, ones;
	} *amount;

	Tree binTree_root;

	size_t length;
	std::string bincode;
};

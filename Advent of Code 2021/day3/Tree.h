#pragma once
#include <iostream>

class Tree
{
public:
	enum SF : unsigned
	{
		SF_ModeO2 = 0b01,
		SF_ModeCO2 = 0b10,

		SF_IsThereZero = 0b100,
		SF_IsThereOne = 0b1000,
	};

	Tree(bool _isHead);

	int insertLine(const std::string&, const size_t&, size_t i = 0);

	void recursiveSearch(std::string&, SF) const;

	void deleteTree();

private:
	char getNext(const SF&) const;
private:
	Tree* next[2];
	uint32_t amount;
	bool isHead;
};


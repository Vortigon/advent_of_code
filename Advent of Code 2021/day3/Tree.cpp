#include "Tree.h"
Tree::Tree(bool _isHead)
	: next{ nullptr }, amount{ 0 }, isHead{ _isHead } {}

int Tree::insertLine(const std::string& bincode, const size_t& length, size_t i)
{
	if (isHead)
	{
		amount++;
	}
	uint16_t digit = bincode[i] - '0';
	if (!next[digit])
	{
		next[digit] = new Tree{ false };
		if (!next[digit])
			return -3;
	}

	next[digit]->amount++;
	if (i + 1 < length)
	{
		return next[digit]->insertLine(bincode, length, i + 1);
	}
	else return 0;
}

void Tree::recursiveSearch(std::string& buffer, SF mode) const
{
	switch (getNext(mode))
	{
	case 0:
	{
		buffer += '0';
		next[0]->recursiveSearch(buffer, mode);
		return;
	}
	case 1:
	{
		buffer += '1';
		next[1]->recursiveSearch(buffer, mode);
		return;
	}
	default:
		return;
	}
}

char Tree::getNext(const SF& mode) const
{
	uint16_t flag = mode;

	flag |= next[0] ? SF_IsThereZero : 0;
	flag |= next[1] ? SF_IsThereOne : 0;

	switch (flag & (SF_IsThereZero | SF_IsThereOne))
	{
	case SF_IsThereZero:
	{
		return 0;
	}
	case SF_IsThereOne:
	{
		return 1;
	}
	case SF_IsThereZero | SF_IsThereOne:
	{
		if (next[0]->amount > next[1]->amount)
		{
			if (flag & SF_ModeO2) { return 0; }
			else { return 1; }
		}
		else
		{
			if (flag & SF_ModeCO2) { return 0; }
			else { return 1; }
		}
	}
	default:
	{ return -1; }
	}
}

void Tree::deleteTree()
{
	if (next[0]) next[0]->deleteTree();
	if (next[1]) next[1]->deleteTree();
	if (!isHead) delete this;
}
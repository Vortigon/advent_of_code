#include "BracketStack.h"

static const char* const opens = "([{<";
static const char* const closes = ")]}>";

BracketStack::BracketStack(size_t size)
	: str_size{ size }, amount{ 0 }, stack{ nullptr }, bracket_amount{ 0 }
{
	if (size == 0)  
	{ throw "\n[ERROR]: Bad string size to create stack!\n"; }

	stack = new char[size] {0};
	if (!stack) 
	{ throw "\n[ERROR]: An error occured while trying to allocate memory.\n"; }
}

bool BracketStack::load(char bracket)
{
	switch (bracket)
	{
	case '(':
	case '<':
	case '[':
	case '{':
	{ return push(bracket); }
	case ')':
	case '>':
	case ']':
	case '}':
	{ return pop(bracket); }
	default: { return false; }
	}
}

bool BracketStack::push(char bracket)
{
	size_t index = getIndex(bracket);
	bracket_amount[index]++;
	stack[amount++] = bracket;
	return true;
}

bool BracketStack::pop(char bracket)
{
	size_t index = getIndex(bracket);
	if ((bracket_amount[index] == 0) || (stack[amount - 1] != opens[index]))
	{
		return false;
	}
	bracket_amount[index]--;
	stack[--amount] = '\0';
	return true;
}

size_t BracketStack::getIndex(char bracket)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (bracket == opens[i] || bracket == closes[i]) return i;
	}
	return 0;
}
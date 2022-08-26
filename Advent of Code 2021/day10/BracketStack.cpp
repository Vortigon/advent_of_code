#include "BracketStack.h"
#include <cstdlib>
BracketStack::BracketStack(size_t size)
	: str_size{ size }, amount{ 0 }, stack{ nullptr }
{
	if (size == 0)  { throw "\n[ERROR]: Bad string size to create stack!\n"; }

	stack = new char[size] {0};
}

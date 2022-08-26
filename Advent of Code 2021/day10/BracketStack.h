#pragma once
class BracketStack
{
public:
	BracketStack() = delete;
	BracketStack(size_t size);
	~BracketStack() { delete[] stack; }


private:

	size_t str_size, amount;
	char* stack;
};


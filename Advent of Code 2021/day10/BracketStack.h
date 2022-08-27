#pragma once
class BracketStack
{
public:
	BracketStack() = delete;
	BracketStack(size_t size);
	~BracketStack() { delete[] stack; }

	bool load(char bracket);
private:
	bool push(char bracket);
	bool pop(char bracket);
	size_t getIndex(char bracket);

	size_t str_size, amount;
	char* stack;
	size_t bracket_amount[4];
};

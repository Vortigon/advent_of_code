/*--- Day 3: Binary Diagnostic ---*/

#include <fstream>
#include <iostream>

class Diagnostic
{
public:
	Diagnostic() : amount{ nullptr }, length{ 0 } {}

	int getline(std::ifstream& file)
	{
		if (!file.is_open()) { return -2; }

		file >> bincode;

		size_t len = bincode.length();
		if (!len) { return -1; }
		length = len;

		if (!amount)
		{
			if ( !allocAmount() )
				{ return -3; }
		}

		for (size_t i = 0; i < length; i++)
		{
			if (bincode[i] == '0') 
			{
				amount[i].zeros++;
				continue; 
			}
			if (bincode[i] == '1') 
			{ amount[i].ones++; }
		}
		binTree_root.getline(bincode, length);
		bincode.clear();
		return 0;
	}

	uint32_t getPowerConsumption() const
	{
		uint32_t gamma{ 0 }, epsilon{ 0 };

		for (uint32_t i = 0; i < length; i++)
		{
			if (amount[i].ones >= amount[i].zeros)
				{ gamma |= 1 << (length - 1 - i); }
			else 
				{ epsilon |= 1 << (length - 1 - i); }
		}

		return gamma * epsilon;
	}

	uint32_t getLifeSupportRating() const
	{
		uint32_t o2{ 0 }, co2{ 0 }, amount{ binTree_root.getAmount() };
		std::string buffer_o2, buffer_co2;

		binTree_root.printTree();

		binTree_root.recursiveSearch(amount, buffer_o2);

		amount = binTree_root.getAmount();
		binTree_root.recursiveSearch2(amount, buffer_co2);
		/*1101 1111 0101 =3573*/

		/*0101 1000 1111 =1423*/
		/*0010 0000 1010 =522*/
		/*"0001 0010 0001 = 289"*/
		return o2 * co2;
	}

	~Diagnostic() { delete[] amount; }

private:
	bool allocAmount()
	{
		amount = new Bin[length];
		if (!amount) return false;
		
		for (size_t i = 0; i < length; i++)
		{
			amount[i].zeros = 0;
			amount[i].ones = 0;
		}
		return true;
	}

private:

	struct Bin
	{
		uint32_t zeros, ones;
	} *amount;

	struct Tree
	{
	public:
		Tree(bool _isHead)
			: next{ nullptr }, amount{ 0 }, isHead{ _isHead } {}

		int getline(/*Tree& tree_root,*/ const std::string& bincode, const size_t& length, size_t i = 0)
		{
			if (isHead) 
			{ amount++; }
			uint8_t digit = bincode[i] - '0';
			if (!next[digit]) 
			{
				next[digit] = new Tree{false};
				if (!next[digit])
					return -3;
			}

			next[digit]->amount++;
			if (i + 1 < length)
			{
				return next[digit]->getline(/*tree_root,*/ bincode, length, i + 1);
			}
			else return 0;
			
			/*else
			{
				if (!next[1])
				{
					next[1] = new Tree{ false };
					if (!next[1])
						return -3;
				}

				next[1]->amount++;
				if (i + 1 < length)
				{
					return next[1]->getline(tree_root, bincode, length, i + 1);
				}
				else return 0;
			}*/
		}

		void recursiveSearch(uint32_t& remain, std::string& buffer) const 
		{
			if ((next[0] == nullptr) && (next[1] == nullptr)) return;

			if ((next[0] != nullptr) && (next[1] != nullptr))
			{
				if (next[1]->amount >= next[0]->amount)
				{
					remain -= next[0]->amount;
					buffer += '1';
					next[1]->recursiveSearch(remain, buffer);
					return;
				}
				else
				{
					remain -= next[1]->amount;
					buffer += '0';
					next[0]->recursiveSearch(remain, buffer);
					return;
				}
			}
			else
			{
				if (next[0] != nullptr)
				{
					buffer += '0';
					next[0]->recursiveSearch(remain, buffer);
					return;
				}
				if (next[1] != nullptr)
				{
					buffer += '1';
					next[1]->recursiveSearch(remain, buffer);
					return;
				}
			}
		}

		void recursiveSearch2(uint32_t& remain, std::string& buffer) const
		{
			if ((next[0] == nullptr) && (next[1] == nullptr)) return;

			if ((next[0] != nullptr) && (next[1] != nullptr))
			{
				if (next[0]->amount <= next[1]->amount)
				{
					remain -= next[1]->amount;
					buffer += '0';
					next[0]->recursiveSearch2(remain, buffer);
					return;
				}
				else
				{
					remain -= next[0]->amount;
					buffer += '1';
					next[1]->recursiveSearch2(remain, buffer);
					return;
				}
			}
			else
			{
				if (next[0] != nullptr)
				{
					buffer += '0';
					next[0]->recursiveSearch2(remain, buffer);
					return;
				}
				if (next[1] != nullptr)
				{
					buffer += '1';
					next[1]->recursiveSearch2(remain, buffer);
					return;
				}
			}
		}

		void printTree(int zero_one = -1,int level = 0) const
		{
			level += 1;
			for (int i = 0; i < level; i++)
				std::cout << "-";
			switch (zero_one)
			{
			case 0: { std::cout << 0 << "|"; break; }
			case 1: {std::cout << 1 << "|"; break; }
			default:
				break;
			}
			if (this)
			{
				std::cout << amount << '\n';
				next[0]->printTree(0, level);
				next[1]->printTree(1, level);
			}
			else std::cout << "0\n";
		}

		uint32_t getAmount() const { return amount; }

	private:
		Tree* next[2];
		uint32_t amount;
		bool isHead;
	} binTree_root{ true };

	size_t length;
	std::string bincode;
};

int main()
{	
	std::ifstream file{ "input.txt" };
	if (!file.is_open()) { exit(-2); }

	Diagnostic tool;
	while (1)
	{
		int err_code{ tool.getline(file) };
		
		if (err_code)
		{
			switch (err_code)
			{
			case -1: 
			{
				std::cout << "Power consumption: " << tool.getPowerConsumption() <<
					"\nLife support rating: " << tool.getLifeSupportRating() << std::endl;
				break; 
			}
			case -2: { std::cout << "Failed to open file\n"; break; }
			case -3: { std::cout << "Failed to allocate memory\n"; break; }
			}
			break;
		}
	}
}

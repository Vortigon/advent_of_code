#include "Digits.h"
Digits::Digits()
	: uniq_digits{ 0 }, segment{ 0 }, sum{ 0 }, read_strings{ 0 } {}

bool Digits::getInput(std::ifstream& file)
{
	if (!file.is_open()) { return false; }

	while (1)
	{
		for (std::string& str : digit_str)
		{
			file >> str;
		}
		if (file.peek() == EOF) { break; }

		deducate();

		file.ignore(3, '|');

		for (int i = 0, factor = 1000; i < 4; i++, factor /= 10)
		{
			std::string output_digit;
			file >> output_digit;

			int digit = decodeDigit(output_digit);
			if (digit == 1 || digit == 4 || digit == 7 || digit == 8) { uniq_digits++; }

			sum += factor * digit;
		}
	}
	return true;
}

void Digits::deducate()
{
	char digit_i[10], digit5_i[3];

	for (char count{ 0 }, i = 0; i < 10; i++)
	{
		switch (digit_str[i].size())
		{
		case SZ_1:
		{digit_i[1] = i; break; }
		case SZ_4:
		{digit_i[4] = i; break; }
		case SZ_7:
		{digit_i[7] = i; break; }
		case SZ_8:
		{digit_i[8] = i; break; }
		case SZ_5:
		{digit5_i[count++] = i; break; }
		case SZ_6:
		{ break; }
		}
	}

	//one_sgm consists of SG_C and SG_F
	char one_sgm[2]
	{
		digit_str[digit_i[1]][0],
		digit_str[digit_i[1]][1]
	};
	//comparing 1 and 7 to find SG_A
	for (const char& i : digit_str[digit_i[7]])
	{
		if (i != one_sgm[0] && i != one_sgm[1])
		{
			segment[SG_A] = i;
			break;
		}
	}

	//comparing 5-SG digits with 1 to find 3
	//which has both of SG_C and SG_F
	for (char i = 0; i < 3; i++)
	{
		char count = 0;
		for (const char& j : digit_str[digit5_i[i]])
		{
			if (j == one_sgm[0] || j == one_sgm[1])
			{
				count++;
				if (count == 2) { break; }
			}
		}

		if (count == 2)
		{
			digit_i[3] = digit5_i[i];
			break;
		}
	}

	//comparing 4 with 3 to find SG_B, which 4 has but 3 hasn't
	//and SG_D, which both of them have
	for (const char& i : digit_str[digit_i[4]])
	{
		if (i == one_sgm[0] || i == one_sgm[1]) { continue; }

		char index{ 0 };
		for (const char& j : digit_str[digit_i[3]])
		{
			if (j == i) break;
			index++;
		}

		if (index == SZ_5)
		{
			segment[SG_B] = i;
		}
		else
		{
			segment[SG_D] = i;
		}
	}

	//searching for SG_G in 3
	for (const char& i : digit_str[digit_i[3]])
	{
		if (i != segment[SG_A] &&
			i != segment[SG_D] &&
			i != one_sgm[0] &&
			i != one_sgm[1])
		{
			segment[SG_G] = i;
			break;
		}
	}

	//comparing SGs of remaining 5-SG numbers(2,5) with SG_B to find 5
	for (char i = 0; i < 3; i++)
	{
		if (digit5_i[i] == digit_i[3]) { continue; }

		for (const char& j : digit_str[digit5_i[i]])
		{
			if (j == segment[SG_B])
			{
				digit_i[5] = digit5_i[i];
				break;
			}
		}

		if (digit_i[5] == digit5_i[i]) { break; }
	}

	//searching for last 5-SG digit that is 2
	for (char i = 0; i < 3; i++)
	{
		if (digit5_i[i] != digit_i[3] && digit5_i[i] != digit_i[5])
		{
			digit_i[2] = digit5_i[i];
			break;
		}
	}

	//searching for SG_F in 5 and for SG_C in 2
	//on each iteration if SG_C wasn't found we also search for SG_E in 2
	for (char i = 0; i < 5; i++)
	{
		if (digit_str[digit_i[5]][i] == one_sgm[0] ||
			digit_str[digit_i[5]][i] == one_sgm[1])
		{
			segment[SG_F] = digit_str[digit_i[5]][i];
		}
		if (digit_str[digit_i[2]][i] == one_sgm[0] ||
			digit_str[digit_i[2]][i] == one_sgm[1])
		{
			segment[SG_C] = digit_str[digit_i[2]][i];
			continue;
		}
		if (digit_str[digit_i[2]][i] != segment[SG_A] &&
			digit_str[digit_i[2]][i] != segment[SG_D] &&
			digit_str[digit_i[2]][i] != segment[SG_G])
		{
			segment[SG_E] = digit_str[digit_i[2]][i];
		}
	}
}

int Digits::decodeDigit(std::string& digit) const
{
	int value{ -1 };
	switch (digit.size())
	{
	case SZ_1:
	{ value = 1; break; }
	case SZ_4:
	{ value = 4; break; }
	case SZ_7:
	{ value = 7; break; }
	case SZ_8:
	{ value = 8; break; }
	case SZ_5:
	{
		for (const char& i : digit)
		{
			if (i == segment[SG_E])
			{
				value = 2;
				break;
			}
			if (i == segment[SG_B])
			{
				value = 5;
				break;
			}
		}
		if (value == -1) { value = 3; }
		break;
	}
	case SZ_6:
	{
		value = 15;
		for (const char& i : digit)
		{
			if (i == segment[SG_C])
			{
				value -= 6;
				continue;
			}
			if (i == segment[SG_E]) { value -= 9; }
		}
		break;
	}
	}
	return value;
}
#pragma once
#include <fstream>

class Digits
{
public:
	Digits();

	bool getInput(std::ifstream& file);
	size_t getUniqDigits() const { return uniq_digits; }
	int getSum() const { return sum; }

private:
	void deducate();
	int decodeDigit(std::string& digit) const;

private:
	enum NumSize
	{
		SZ_1 = 2,
		SZ_4 = 4,
		SZ_5 = 5,
		SZ_6 = 6,
		SZ_7 = 3,
		SZ_8 = 7,
	};

	enum SegmentIndex
	{
		SG_A = 0,
		SG_B,
		SG_C,
		SG_D,
		SG_E,
		SG_F,
		SG_G,
	};

	size_t uniq_digits;
	char segment[7];
	int sum;
	std::string digit_str[10];
};


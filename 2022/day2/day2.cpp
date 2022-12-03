#include <iostream>
#include <fstream>
#include <map>

enum class GameResult
{
	WIN, DRAW, LOSE
};

int gameCheck(char enemy, char mc)
{
	if ((enemy == 'B' && mc == 'X')
	|| (enemy == 'C' && mc == 'Y')
	|| (enemy == 'A' && mc == 'Z'))
	{ return 0; }

	if ((enemy == 'A' && mc == 'X')
	|| (enemy == 'B' && mc == 'Y')
	|| (enemy == 'C' && mc == 'Z'))
	{ return 3; }

	if ((enemy == 'C' && mc == 'X')
	|| (enemy == 'A' && mc == 'Y')
	|| (enemy == 'B' && mc == 'Z'))
	{ return 6; }

	exit(2);
}

char newGameCheck(char enemy, char result)
{
	if ((result == 'X' && enemy == 'B')
	|| (result == 'Y' && enemy == 'A')
	|| (result == 'Z' && enemy == 'C'))
	{ return 'X'; }

	if ((result == 'X' && enemy == 'C')
	|| (result == 'Y' && enemy == 'B')
	|| (result == 'Z' && enemy == 'A'))
	{ return 'Y'; }

	if ((result == 'X' && enemy == 'A')
	|| (result == 'Y' && enemy == 'C')
	|| (result == 'Z' && enemy == 'B'))
	{ return 'Z'; }
	
	exit(3);
}
int main()
{
	std::map<char, int> scores = {
		{'X', 1},
		{'Y', 2},
		{'Z', 3}
	};

	std::map<char, int> result_scores = {
		{'X', 0},
		{'Y', 3},
		{'Z', 6}
	};
	
	std::fstream fs("input.txt");
	if (!fs.is_open()) { exit(1); }

	char buffer[5];
	int total_score{0};
	int true_score{0};

	while(fs.getline(buffer, 5))
	{
		total_score += scores.find(buffer[2])->second;
		total_score += gameCheck(buffer[0], buffer[2]);

		int score = result_scores.find(buffer[2])->second;
		score += scores.find(newGameCheck(buffer[0], buffer[2]))->second;
		true_score += score;
	}
	std::cout << "Total score is " << total_score << std::endl;
	std::cout << "But true score is " << true_score << std::endl << std::endl;
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class BingoBoard
{
public:
	BingoBoard()
		: number{ 0 }, marked{ false } {}

	bool operator<<(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }

		for (size_t loaded{ 0u }; loaded < 25u; loaded++)
		{
			int new_num;
			file >> new_num;

			if (file.peek() == EOF) { return false; }

			number[loaded / 5u][loaded % 5u] = new_num;
		}

		return true;
	}

	bool play(std::vector<int> &row,  int& old_turns, int& score, bool squid_must_win)
	{
		int turn{ 0 }, last_mark{ 26 };

		for (const int& row_num : row)
		{
			last_mark = mark(row_num);
			turn++;
			if (!squid_must_win && turn >= old_turns && old_turns >= 5) { return false; }

			if (turn >= 5 && last_mark < 25)
			{
				if(winCheck(last_mark))
				{
					if ( (squid_must_win && turn > old_turns) || 
						(!squid_must_win && (old_turns < 5 || turn < old_turns) ) )
					{
						old_turns = turn;
						score = getScore(number[last_mark / 5][last_mark % 5]);
						return true;
					}
					else { return false; }
				}
			}
		}
		return false;
	}
private:
	size_t mark(int row_num)
	{
		for (size_t i{0u}; i < 25u; i++)
		{
			if (number[i / 5u][i % 5u] == row_num)
			{
				marked[i / 5u][i % 5u] = true;
				return i;
			}
		}
		return 26;
	}

	bool winCheck(size_t last_mark) const
	{
		for (size_t i{ 0 }; i < 5u; i++)
		{
			if (!marked[last_mark / 5][i]) { break; }
			if (i == 4) { return true; }
		}

		for (size_t i{ 0 }; i < 5u; i++)
		{
			if (!marked[i][last_mark % 5]) { break; }
			if (i == 4) { return true; }
		}
		return false;
	}

	int getScore(int& last_mark)
	{
		int score{ 0 };
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				if (!marked[i][j]) score += number[i][j];
			}
		}
		return last_mark * score;
	}

private:
	int number[5][5];
	bool marked[5][5];
};

class Bingo
{
public:
	Bingo(bool squid)
		: board_won{ 0 }, squid_must_win{ squid } {}

	~Bingo() { row.~vector(); }

	int getInput(std::ifstream& file)
	{
		if (!file.is_open()) { return -2; }

		while (file.peek() != '\n')
		{
			int new_num;
			file >> new_num;
			row.push_back(new_num);
			file.ignore(1, ',');
		}
		row.shrink_to_fit();

		for (int board_i{ 1 }; playBoard(file, board_i); board_i++) {}

		return 0;
	}

	void printWonBoardInfo() const
	{
		if (board_won.turn)
		{
			if (!squid_must_win)
			{
				std::cout << "Board #" << board_won.number <<
					" won on turn " << board_won.turn <<
					" with score " << board_won.score << std::endl;
			}
			else
			{
				std::cout << "Your board is #" << board_won.number <<
				".\nIt will win last of all boards on turn " << board_won.turn <<
				" with score " << board_won.score <<
				" letting squid win." << std::endl;
			}
		}
		else
		{ std::cout << "No winnings." << std::endl; }
	}

private:
	bool playBoard(std::ifstream& file, int& number)
	{
		BingoBoard board;
		if (!(board << file)) { return false; }

		if (board.play(row, board_won.turn, board_won.score, squid_must_win))
		{ board_won.number = number; }

		return true;
	}

	struct BoardWon
	{
		int number, turn, score;
	} board_won;

	bool squid_must_win;
	std::vector<int> row;
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) exit(-2);

	Bingo bingo1{ false }, bingo2{ true };

	bingo1.getInput(file);
	bingo1.printWonBoardInfo();

	file.close();

	file.open("input.txt");
	if (!file.is_open()) exit(-2);

	bingo2.getInput(file);
	bingo2.printWonBoardInfo();

}

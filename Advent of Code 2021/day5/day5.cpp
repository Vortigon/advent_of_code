/*--- Day 5: Hydrothermal Venture ---*/

#include <iostream>
#include <fstream>

struct Vec2
{
	Vec2()
		: x{ 0 }, y{ 0 } {}
	Vec2(int _x, int _y)
		: x{ _x }, y{ _y } {}
	Vec2(const Vec2& vec)
		: x{ vec.x }, y{ vec.y } {}

	bool load(std::ifstream& file)
	{
		file >> x;
		if (file.peek() == EOF) return false;
		file.ignore(1, ',');
		file >> y;
		return true;
	}

	Vec2& operator=(const Vec2& vec)
	{
		if (!(this == &vec))
		{
			x = vec.x;
			y = vec.y;
		}
		return (*this);
	}

	Vec2 operator-(const Vec2& vec) const
	{
		return Vec2{ x - vec.x, y - vec.y };
	}
	
	Vec2 operator+(const Vec2& vec) const
	{
		return Vec2{ x + vec.x, y + vec.y };
	}

	Vec2& operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	bool operator!=(const Vec2& vec)
	{
		return (x != vec.x || y != vec.y);
	}

	int x, y;
};

struct VentLine
{
	VentLine()
		: pos{}, dir{} {}

	bool load(std::ifstream& file)
	{
		if (!pos.load(file)) { return false; }

		std::string buf;
		file >> buf;

		Vec2 pos2;
		pos2.load(file);
		dir = pos2 - pos;
		if (dir.x && dir.y && ( (dir.x != dir.y) && (dir.x != -dir.y) ) ) return false;
		return true;
	}

	Vec2 pos, dir;
};

class Matrix
{
public:
	Matrix(bool diagonal)
		: matrix{ 0 }, count_diagonals{ diagonal } {};

	bool inputVentLine(std::ifstream& file)
	{
		if (!file.is_open()) { return false; }

		VentLine line;

		if (!line.load(file)) return false;
		markLine(line);

		return true;
	}

	int getCrossCount() const
	{
		int count{ 0 };
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrix[j][i] > 1) { count++; }
			}
		}
		return count;
	}
private:
	void markLine(const VentLine& line)
	{
		Vec2 iter, begin{ line.pos }, end{ line.pos + line.dir };
		if (line.dir.x > 1) { iter.x = 1; }
		else if (line.dir.x < 0) { iter.x = -1; }

		if (line.dir.y > 1) { iter.y = 1; }
		else if (line.dir.y < 0) { iter.y = -1; }

		if ((!count_diagonals) && (iter.x && iter.y))
		{ return; }

		while (begin != end)
		{
			matrix[begin.x][begin.y]++;
			begin += iter;
		}
		matrix[begin.x][begin.y]++;
	}
	static constexpr size_t size{ 1000 };

	uint16_t matrix[size][size];
	bool count_diagonals;
};

int main()
{
	std::ifstream file("input.txt");
	if (!file.is_open()) { exit(-2); }

	Matrix* mat = new Matrix{ false };

	while (mat->inputVentLine(file));
	std::cout << "Without diagonals: " << mat->getCrossCount() << std::endl;

	file.close();
	delete mat;

	file.open("input.txt");
	if (!file.is_open()) { exit(-2); }

	mat = new Matrix{ true };
	
	while (mat->inputVentLine(file));
	std::cout << "With diagonals: " << mat->getCrossCount() << std::endl;

}
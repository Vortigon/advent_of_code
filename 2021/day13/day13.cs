using System.Text;

namespace aoc_day13
{
	class Program
	{
		static void Main()
		{
			HashSet<(int x, int y)> dots = new HashSet<(int x, int y)>();
			StreamReader input = new("input.txt");
			while (true)
			{
				string read_input = input.ReadLine();
				if (read_input == "") { break; }
				string[] read_coords = read_input.Split(',');
				int x = int.Parse(read_coords[0]);
				int y = int.Parse(read_coords[1]);
				dots.Add((x, y));
			}

			while (true)
			{
				string? folding = input.ReadLine()?.Replace("fold along ", "");
				if (folding == null) { break; }
				char fold_axis = folding[0];
				int fold_coord = int.Parse(folding.Replace(folding.Substring(0, 2), ""));


				dots = fold(dots, fold_axis, fold_coord);

			}
			input.Close();

			int columns = 0;
			int rows = 0;
			foreach (var dot in dots)
			{
				columns = int.Max(columns, dot.x);
				rows = int.Max(rows, dot.y);
			}
			StreamWriter output = new StreamWriter("output.txt");
			for (int i = 0; i <= rows; i++)
			{
				var output_string = new StringBuilder(new String('.', columns + 1));
				foreach (var dot in dots)
				{
					if (dot.y == i)
					{
						output_string.Replace('.', '#', dot.x, 1);
					}
				}
				output.WriteLine(output_string);
			}
			output.Close();
		}

		static HashSet<(int x, int y)> fold(HashSet<(int x, int y)> dots, char axis, int fold_coord)
		{
			HashSet<(int x, int y)> new_set = new HashSet<(int x, int y)>();
			if (axis == 'x')
			{
				foreach (var dot in dots)
				{
					int new_x = dot.x > fold_coord ? fold_coord - (dot.x - fold_coord) : dot.x;
					new_set.Add((new_x, dot.y));
				}
			}
			else
			{
				foreach (var dot in dots)
				{
					int new_y = dot.y > fold_coord ? fold_coord - (dot.y - fold_coord) : dot.y;
					new_set.Add((dot.x, new_y));
				}
			}
			return new_set;
		}
	}
}
using System;
using System.Numerics;
using System.IO;

namespace aoc_day13
{
	class Program
	{

		class DotsEquailtyComparer : IEqualityComparer<int[]>
		{
			public bool Equals(int[]? value1, int[]? value2)
			{
				if (value1 == null || value2 == null) return false;
				return value1[0] == value2[0] && value1[1] == value2[1];
			}
			public int GetHashCode(int[] value)
			{
				int hash = 23 * 31 + value[0];
				hash = hash * 31 + value[1];
				return hash;
			}
		}
		static void Main()
		{
			HashSet<int[]> dots = new HashSet<int[]>(new DotsEquailtyComparer());
			//LinkedList<int[]> dots = new LinkedList<int[]>();
			StreamReader input = new("input.txt");
			while(true)
			{
                string read_input = input.ReadLine();
				if (read_input == "") { break; }
				string[] read_coords = read_input.Split(',');

                int[] coords = new int[2];
                for (int i = 0; i < read_coords.Length; ++i)
                {
					coords[i] = Int32.Parse(read_coords[i]);
                }
				dots.Add(coords);
			}

			string folding = input.ReadLine().Replace("fold along ", "");
			char fold_axis = folding[0];
			int fold_coord = Int32.Parse(folding.Replace(folding.Substring(0, 2), ""));
			Console.WriteLine(fold_axis);
            Console.WriteLine(fold_coord);
			Console.WriteLine(dots.Count);

            fold(dots, fold_axis, fold_coord);
			Console.WriteLine("Total dots after first fold: " + dots.Count);
        }

		static void fold(HashSet<int[]> dots, char axis, int fold_coord)
		{
			int folding_coord = axis == 'x' ? 0 : 1;
            foreach (var dot in dots)
            {
                if (dot[folding_coord] > fold_coord)
				{
					
					int[] new_dot = new int[] { 0,0 };
					dot.CopyTo(new_dot, 0);
					new_dot[folding_coord] = dot[folding_coord] - 2 * (dot[folding_coord] - fold_coord);

                    if (dots.Contains(new_dot)) {
						dots.Remove(dot); 
					}
					else {
						dot[folding_coord] = new_dot[folding_coord]; 
					}
				}
            }
        }
	}
}
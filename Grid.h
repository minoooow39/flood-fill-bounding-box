#pragma once
#include <algorithm>
#include <vector>

namespace FloodFill
{
	struct Rect
	{
		int top{};
		int bottom{};
		int left{};
		int right{};

		Rect()
		{}
		Rect(int top, int bottom, int left, int right) : top(top), bottom(bottom), left(left), right(right)
		{}
	};

	enum Algorithm
	{
		RecursiveDFS,
		StackDFS,
		QueueBFS
	};

	class Grid
	{
	public:
		Grid(const std::vector<char>& grid, int height, int width, Algorithm algo);
	private:
		int const height{};
		int const width{};
		std::vector<char> grid;
		int minX{ INT_MAX };
		int minY{ INT_MAX };
		int maxX{ -1 };
		int maxY{ -1 };

		Rect boundaries;

		Algorithm algo = Algorithm::QueueBFS;

		void FindBoundingBox();

		void RecursionFloodFill(int index);
		void DFSFloodFill(int index);
		void BFSFloodFill(int index);

		void SetBoundaries();

	public:
		const Rect& GetBoundaries();
	};
}
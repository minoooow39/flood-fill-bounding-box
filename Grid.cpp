#include "Grid.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

namespace FloodFill
{
	Grid::Grid(const std::vector<char>& grid, int height, int width, Algorithm algo) : grid(grid), height(height), width(width), algo(algo)
	{
	}

	void Grid::FindBoundingBox()
	{
		// for each pixel
		for (int i{ 0 }; i < height * width; ++i)
		{
			// if colored pixel is found i.e. value is not 0 (not colored) or -1 (marked as found)
			if (grid[i] > 0)
			{
				switch (algo)
				{
				case(Algorithm::RecursiveDFS):
					RecursionFloodFill(i);
					break;
				case(Algorithm::StackDFS):
					DFSFloodFill(i);
					break;
				case(Algorithm::QueueBFS):
					BFSFloodFill(i);
					break;
				}
			}
		}
		SetBoundaries();
		return;
	}

	void Grid::RecursionFloodFill(int index)
	{
		if (index < 0 || index >= height * width || grid[index] <= 0)
			return;

		grid[index] = -1;

		int x = index / width;
		int y = index % width;
		minX = std::min(minX, y);
		minY = std::min(minY, x);
		maxX = std::max(maxX, y);
		maxY = std::max(maxY, x);

		RecursionFloodFill(index + width); // go down
		RecursionFloodFill(index - width); // go up
		RecursionFloodFill(index + 1); // go right
		RecursionFloodFill(index - 1); // go left
	}

	void Grid::DFSFloodFill(int index)
	{
		std::stack<char> pathStack{};

		grid[index] = -1;

		pathStack.push(index);

		while (!pathStack.empty())
		{
			int current = pathStack.top();
			pathStack.pop();

			if (grid[current] == -1)
			{
				int x = index / width;
				int y = index % width;
				minX = std::min(minX, y);
				minY = std::min(minY, x);
				maxX = std::max(maxX, y);
				maxY = std::max(maxY, x);
			}

			// down, up, right, left
			int neighbors[] = { index + width, index - width, index + 1, index - 1 };
			for (auto& i : neighbors)
			{
				if (i < 0 || i >= height * width || grid[i] <= 0) continue;
				grid[i] = -1;

				pathStack.push(i);
			}
		}
	}

	void Grid::BFSFloodFill(int index)
	{
		std::queue<char> pathQueue{};

		grid[index] = -1;

		pathQueue.push(index);

		while (!pathQueue.empty())
		{
			int current = pathQueue.front();
			pathQueue.pop();

			if (grid[current] == -1)
			{
				int x = index / width;
				int y = index % width;
				minX = std::min(minX, y);
				minY = std::min(minY, x);
				maxX = std::max(maxX, y);
				maxY = std::max(maxY, x);
			}

			// down, up, right, left
			int neighbors[] = { index + width, index - width, index + 1, index - 1 };
			for (auto& i : neighbors)
			{
				if (i < 0 || i >= height * width || grid[i] <= 0) continue;
				grid[i] = -1;

				pathQueue.push(i);
			}
		}
	}

	void Grid::SetBoundaries()
	{
		boundaries.top = minY;
		boundaries.left = minX;
		boundaries.bottom = maxY;
		boundaries.right = maxX;
	}

	const Rect& Grid::GetBoundaries()
	{
		FindBoundingBox();
		return boundaries;
	}
}

#include "Grid.h"

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

int main()
{
	// arbitrary rules:
	// 0 = no color
	// >0 = colored
	std::vector<int> image = {
		0, 0, 3, 0, 0,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 0, 0, 0, 0
	};

	// will mutate the image
	FloodFill::Grid grid = FloodFill::Grid(image, FloodFill::Algorithm::QueueBFS);

	FloodFill::Rect imageBoundaries = grid.GetBoundaries();

	std::cout << "Bounding Box: " <<
		"Top Left: (" << imageBoundaries.left << ", " << imageBoundaries.top << ")\n" <<
		"Top Right: (" << imageBoundaries.right << ", " << imageBoundaries.top << ")\n" <<
		"Bottom Left: (" << imageBoundaries.left << ", " << imageBoundaries.bottom << ")\n" <<
		"Bottom Right: (" << imageBoundaries.right << ", " << imageBoundaries.bottom << ")\n";

	return 0;
}
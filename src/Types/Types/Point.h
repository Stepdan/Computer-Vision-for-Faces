#pragma once

#include <vector>

namespace Types {

struct Point
{
	Point(int X, int Y) : x(X), y(Y) {}
	int x, y;
};

using PairPoint = std::pair<Point, Point>;
using Contour  = std::vector<Point>;
using Contours = std::vector<Contour>;

}

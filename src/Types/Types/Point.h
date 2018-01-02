#pragma once

#include <iosfwd>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>

#include <string>
#include <vector>

namespace Types {

struct Point
{
	Point() = default;
	Point(int X, int Y) : x(X), y(Y) {}
	int x, y;
};

using PairPoint = std::pair<Point, Point>;
using Contour  = std::vector<Point>;
using Contours = std::vector<Contour>;

std::ofstream& operator<<(std::ofstream & stream, const Types::Point & point);
std::ofstream& operator<<(std::ofstream & stream, const Types::Contour & contour);
std::ofstream& operator<<(std::ofstream & stream, const Types::Contours & contours);

}

#include "Point.h"

namespace Types {

std::ofstream& operator<<(std::ofstream & stream, const Types::Point & point)
{
	stream << std::to_string(point.x) << " " << std::to_string(point.y) << std::endl;
	return stream;
}

std::ofstream& operator<<(std::ofstream & stream, const Types::Contour & contour)
{
	for (const auto &point : contour)
		stream << point;
	return stream;
}

std::ofstream& operator<<(std::ofstream & stream, const Types::Contours & contours)
{
	for (const auto &contour : contours)
		stream << contour;
	return stream;
}

}

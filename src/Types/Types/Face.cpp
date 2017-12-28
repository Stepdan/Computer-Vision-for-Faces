#include "Face.h"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace {

constexpr size_t FACE = 0;
constexpr size_t EYEBROW_LEFT = 17;
constexpr size_t EYEBROW_RIGHT = 22;
constexpr size_t NOSE_VERTICAL = 27;
constexpr size_t NOSE_HORIZONTAL = 31;
constexpr size_t EYE_LEFT = 36;
constexpr size_t EYE_RIGHT = 42;
constexpr size_t MOUTH_OUTER = 48;
constexpr size_t MOUTH_INNER = 60;
constexpr size_t PUPILS_POINTS = 68;
constexpr size_t POINTS_COUNT = 70;

}

namespace Types {

Face::Face(const Contour & outline, const Contours & eyeBrows, const Contours & eyes,
	 const Contours & nose, const Contours & mouth, const PairPoint & frame, const PairPoint & pupils/* = PairPoint()*/)
	: m_outline(outline)
	, m_eyeBrows(eyeBrows)
	, m_eyes(eyes)
	, m_nose(nose)
	, m_mouth(mouth)
	, m_frame(frame)
	, m_pupils(pupils)
{
}

Face::Face(const Face& rhs)
{
	this->m_outline  = rhs.m_outline;
	this->m_eyeBrows = rhs.m_eyeBrows;
	this->m_eyes     = rhs.m_eyes;
	this->m_nose     = rhs.m_nose;
	this->m_mouth    = rhs.m_mouth;
	this->m_frame    = rhs.m_frame;
	this->m_pupils   = rhs.m_pupils;
}

Contour Face::GetAllPoints()
{
	Contour contour;

	std::copy(m_outline    .begin(), m_outline    .end(), std::back_inserter(contour));
	std::copy(m_eyeBrows[0].begin(), m_eyeBrows[0].end(), std::back_inserter(contour));
	std::copy(m_eyeBrows[1].begin(), m_eyeBrows[1].end(), std::back_inserter(contour));
	std::copy(m_nose[0]    .begin(), m_nose[0]    .end(), std::back_inserter(contour));
	std::copy(m_nose[1]    .begin(), m_nose[1]    .end(), std::back_inserter(contour));
	std::copy(m_eyes[0]    .begin(), m_eyes[0]    .end(), std::back_inserter(contour));
	std::copy(m_eyes[1]    .begin(), m_eyes[1]    .end(), std::back_inserter(contour));
	std::copy(m_mouth[0]   .begin(), m_mouth[0]   .end(), std::back_inserter(contour));
	std::copy(m_mouth[1]   .begin(), m_mouth[1]   .end(), std::back_inserter(contour));

	contour.push_back(m_pupils.first);
	contour.push_back(m_pupils.second);

	return contour;
}

size_t Face::GetLandmarkIndex(const Point & pnt)
{
	const auto points = GetAllPoints();
	std::vector<int> dist(points.size());
	for(size_t i = 0; i < points.size(); ++i)
		dist[i] = sqrt((points[i].x - pnt.x)*(points[i].x - pnt.x) + (points[i].y - pnt.y)*(points[i].y - pnt.y));

	return distance(dist.begin(), std::min_element(dist.begin(), dist.end()));
}

void Face::SetLandmark(size_t index, const Point & pnt)
{
	if(index < EYEBROW_LEFT)
		m_outline[index] = pnt;
	else if(index < EYEBROW_RIGHT)
		m_eyeBrows[0][index-EYEBROW_LEFT] = pnt;
	else if(index < NOSE_VERTICAL)
		m_eyeBrows[1][index - EYEBROW_RIGHT] = pnt;
	else if(index < NOSE_HORIZONTAL)
		m_nose[0][index - NOSE_VERTICAL] = pnt;
	else if(index < EYE_LEFT)
		m_nose[1][index - NOSE_HORIZONTAL] = pnt;
	else if(index < EYE_RIGHT)
		m_eyes[0][index - EYE_LEFT] = pnt;
	else if(index < MOUTH_OUTER)
		m_eyes[1][index - EYE_RIGHT] = pnt;
	else if(index < MOUTH_INNER)
		m_mouth[0][index - MOUTH_OUTER] = pnt;
	else if(index < PUPILS_POINTS)
		m_mouth[1][index - MOUTH_INNER] = pnt;
	else if(index < POINTS_COUNT)
		(index == 68) ? m_pupils.first = pnt : m_pupils.second = pnt;
}

}

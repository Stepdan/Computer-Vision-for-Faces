#include "Face.h"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace {

// Инвертированные значения индексов
std::vector<int> g_invertedIndexes = {
	16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, // outline
	26, 25, 24, 23, 22, 21, 20, 19, 18, 17,                   // eyeBrows
	27, 28, 29, 30, 35, 34, 33, 32, 31,                       // nose
	45, 44, 43, 42, 47, 46, 39, 38, 37, 36, 41, 40,           // eyes
	54, 53, 52, 51, 50, 49, 48, 59, 58, 57, 56, 55,           // outer mouse
	64, 63, 62, 61, 60, 67, 66, 65,                           // inner mouse
	69, 68                                                    // pupils
};

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

Face::Face(const Contour & contour)
{
	SetPoints(contour);

	const auto predicatX = [](const Point & p0, const Point & p1) { return p0.x < p1.x; };
	const auto predicatY = [](const Point & p0, const Point & p1) { return p0.y < p1.y; };

	m_frame.first.x  = std::min_element(contour.cbegin(), contour.cend(), predicatX)->x;
	m_frame.first.y  = std::min_element(contour.cbegin(), contour.cend(), predicatY)->y;
	m_frame.second.x = std::max_element(contour.cbegin(), contour.cend(), predicatX)->x;
	m_frame.second.y = std::max_element(contour.cbegin(), contour.cend(), predicatY)->y;
}

Face::Face(const Contour & contour, const PairPoint & frame)
{
	SetPoints(contour);
	SetFrame(frame);
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

Contour Face::GetInvertedPoints(int width)
{
	Contour contour;

	auto buf = GetAllPoints();
	for(auto & pnt : buf)
		pnt.x = width - pnt.x;

	contour.resize(POINTS_COUNT);
	for(size_t i = 0; i < buf.size(); ++i)
		contour[i] = buf[g_invertedIndexes[i]];

	return contour;
}

PairPoint Face::GetInvertedFrame(int width)
{
	auto inverted = m_frame;
	inverted.first.x = width - inverted.first.x;
	inverted.second.x = width - inverted.second.x;
	std::swap(inverted.first.x, inverted.second.x);
	return inverted;
}

size_t Face::GetLandmarkIndex(const Point & pnt)
{
	const auto points = GetAllPoints();
	std::vector<int> dist(points.size());
	for(size_t i = 0; i < points.size(); ++i)
		dist[i] = sqrt((points[i].x - pnt.x)*(points[i].x - pnt.x) + (points[i].y - pnt.y)*(points[i].y - pnt.y));

	return distance(dist.begin(), std::min_element(dist.begin(), dist.end()));
}

void Face::SetPoints(const Contour & contour)
{
	Contour faceContour
		, leftEyebrow, rightEyebrow
		, noseVertical, noseHorizontal
		, leftEye, rightEye
		, mouthOuter, mouthInner
		;

	// раскладываем точки лиц по компонентам
	for (size_t i = FACE; i < EYEBROW_LEFT; ++i)
		faceContour.push_back({ contour[i].x, contour[i].y });
	for (size_t i = EYEBROW_LEFT; i < EYEBROW_RIGHT; ++i)
		leftEyebrow.push_back({ contour[i].x, contour[i].y });
	for (size_t i = EYEBROW_RIGHT; i < NOSE_VERTICAL; ++i)
		rightEyebrow.push_back({ contour[i].x, contour[i].y });
	for (size_t i = NOSE_VERTICAL; i < NOSE_HORIZONTAL; ++i)
		noseVertical.push_back({ contour[i].x, contour[i].y });
	for (size_t i = NOSE_HORIZONTAL; i < EYE_LEFT; ++i)
		noseHorizontal.push_back({ contour[i].x, contour[i].y });
	for (size_t i = EYE_LEFT; i < EYE_RIGHT; ++i)
		leftEye.push_back({ contour[i].x, contour[i].y });
	for (size_t i = EYE_RIGHT; i < MOUTH_OUTER; ++i)
		rightEye.push_back({ contour[i].x, contour[i].y });
	for (size_t i = MOUTH_OUTER; i < MOUTH_INNER; ++i)
		mouthOuter.push_back({ contour[i].x, contour[i].y });
	for (size_t i = MOUTH_INNER; i < PUPILS_POINTS; ++i)
		mouthInner.push_back({ contour[i].x, contour[i].y });

	m_outline.clear();
	m_eyeBrows.clear(); m_eyeBrows.resize(2);
	m_nose.clear(); m_nose.resize(2);
	m_eyes.clear(); m_eyes.resize(2);
	m_mouth.clear(); m_mouth.resize(2);

	m_outline.swap(faceContour);
	m_eyeBrows[0].swap(leftEyebrow);
	m_eyeBrows[1].swap(rightEyebrow);
	m_nose[0].swap(noseVertical);
	m_nose[1].swap(noseHorizontal);
	m_eyes[0].swap(leftEye);
	m_eyes[1].swap(rightEye);
	m_mouth[0].swap(mouthOuter);
	m_mouth[1].swap(mouthInner);

	m_pupils.first = contour[PUPILS_POINTS];
	m_pupils.second = contour[PUPILS_POINTS+1];
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

std::ofstream& operator<<(std::ofstream & stream, const Face &face)
{
		stream
		<< face.GetOutline()
		<< face.GetEyeBrows()
		<< face.GetNose()
		<< face.GetEyes()
		<< face.GetMouth()
		<< face.GetPupils().first
		<< face.GetPupils().second
		;

		return stream;
}

}

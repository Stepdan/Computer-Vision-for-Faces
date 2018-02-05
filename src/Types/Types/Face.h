#pragma once

#include <iosfwd>

#include "Types/Point.h"

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

namespace Types {

class Face
{
public:
	Face() = default;
	Face(const Contour & contour);
	Face(const Contour & contour, const PairPoint & frame);
	Face(const Contour & outline, const Contours & eyeBrows, const Contours & eyes,
		 const Contours & Nose, const Contours & mouth, const PairPoint & frame, const PairPoint & pupils);
	Face(const Face& rhs);
	~Face() = default;

	void SetFrame   (const PairPoint & value) { m_frame    = value; }
	void SetPupils  (const PairPoint & value) { m_pupils   = value; }
	void SetOutline (const Contour   & value) { m_outline  = value; }
	void SetEyeBrows(const Contours  & value) { m_eyeBrows = value; }
	void SetEyes    (const Contours  & value) { m_eyes     = value; }
	void SetNose    (const Contours  & value) { m_nose     = value; }
	void SetMouth   (const Contours  & value) { m_mouth    = value; }

	const PairPoint & GetFrame    () const { return m_frame    ; }
	const PairPoint & GetPupils   () const { return m_pupils   ; }
	const Contour   & GetOutline  () const { return m_outline  ; }
	const Contours  & GetEyeBrows () const { return m_eyeBrows ; }
	const Contours  & GetEyes     () const { return m_eyes     ; }
	const Contours  & GetNose     () const { return m_nose     ; }
	const Contours  & GetMouth    () const { return m_mouth    ; }

	void SetPoints(const Contour & contour);
	Contour GetAllPoints();
	Contour GetInvertedPoints(int width);
	PairPoint GetInvertedFrame(int width);
	size_t GetLandmarkIndex(const Point &);
	void SetLandmark(size_t, const Point &);

private:
	Contour  m_outline;
	Contours m_eyeBrows;
	Contours m_eyes;
	Contours m_nose;
	Contours m_mouth;

	PairPoint m_frame;
	PairPoint m_pupils;
};

using Faces = std::vector<Face>;
using FacePair = std::pair<Face, Face>;

std::ofstream& operator<<(std::ofstream & stream, const Face &face);

}

#pragma once

#include <iosfwd>

#include "Types/Point.h"

namespace Types {

class Face
{
public:
	Face() = default;
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

std::ofstream& operator<<(std::ofstream & stream, const Face &face);

}

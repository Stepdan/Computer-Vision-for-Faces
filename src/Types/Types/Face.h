#pragma once

#include "Types/Point.h"

namespace Types {

class Face
{
public:
	Face() = default;
	Face(const Contour & outline, const Contours & eyeBrows, const Contours & eyes,
		 const Contours & Nose, const Contours & mouth, const PairPoint & frame, const PairPoint & pupils);
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

}

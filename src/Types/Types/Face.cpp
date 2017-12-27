#include "Face.h"

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

}

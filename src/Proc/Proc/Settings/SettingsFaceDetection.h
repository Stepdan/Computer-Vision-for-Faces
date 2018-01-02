#pragma once

#include <cassert>

#include "BaseSettings.h"

#include "Types/Face.h"

using namespace Types;

namespace Proc {

class SettingsFaceDetection : public BaseSettings
{
public:
	PROC_SETTINGS(SettingsFaceDetection)

	SettingsFaceDetection() = default;

	void AddFace(const Face & face) { m_faces.push_back(face); }

	const Face & GetFace(size_t i) const { return m_faces[i]; }
	const Faces & GetFaces() const { m_faces; }
	size_t GetFacesCount() const { return m_faces.size(); }

	bool DrawWithLandmarks() const { return m_drawWithLandmarks; }
	void SetDrawWithLandmarks(bool value) { m_drawWithLandmarks = value; }

private:
	Faces m_faces;
	bool m_drawWithLandmarks = true;
};

}

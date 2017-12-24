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

	const Face & GetFace(size_t i) const { assert (i > -1 && i < m_faces.size()); return m_faces[i]; }
	const Faces & GetFaces() const { m_faces; }
	size_t GetFacesCount() const { return m_faces.size(); }

private:
	Faces m_faces;
};

}

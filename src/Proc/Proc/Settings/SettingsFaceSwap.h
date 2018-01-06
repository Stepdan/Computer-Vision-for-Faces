#pragma once

#include <cassert>

#include "BaseSettings.h"

#include "Types/Face.h"

using namespace Types;

namespace Proc {

class SettingsFaceSwap : public BaseSettings
{
public:
	PROC_SETTINGS(SettingsFaceSwap)

	SettingsFaceSwap() = default;

	void SetFaces(const FacePair & faces) { m_faces = faces; }
	FacePair GetFaces() const { return m_faces; }

private:
	FacePair m_faces;
};

}

#pragma once

#include <cassert>

#include "BaseSettings.h"

#include "Types/Face.h"

using namespace Types;

namespace Proc {

class SettingsDrawLandmarks : public BaseSettings
{
public:
	PROC_SETTINGS(SettingsDrawLandmarks)

	SettingsDrawLandmarks() = default;

	void SetFace(const Face & face) { m_face = face; }
	Face GetFace() const { return m_face; }

private:
	Face m_face;
};

}

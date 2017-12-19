#pragma once

#include "BaseSettings.h"

namespace Proc {

class SettingsFilter : public BaseSettings
{
public:
	enum class FilterType
	{
		Clarendon,
		Kelvin,
		Moon,
		XProII,
		PencilSketch,
		Cartoon
	};

public:
	PROC_SETTINGS(SettingsFilter)

	SettingsFilter(FilterType type = FilterType::Clarendon) : m_type(type) {}

	void SetFilterType(FilterType type) { m_type = type; }
	void SetVignetteScale(float scale) { m_vignetteScale = scale; }

	FilterType GetFilterType() const { return m_type; }
	float GetVignetteScale() const { return m_vignetteScale; }

private:
	FilterType m_type;
	float m_vignetteScale = 3.0;
};

}

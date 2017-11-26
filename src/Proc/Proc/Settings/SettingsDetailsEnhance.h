#pragma once

#include "BaseSettings.h"

namespace Proc {

class SettingsDetailsEnhance : public BaseSettings
{
public:
	PROC_SETTINGS(SettingsDetailsEnhance)

	SettingsDetailsEnhance() = default;

	void SetSigmaS(float value) { m_sigma_s = value; }
	void SetSigmaR(float value) { m_sigma_r = value; }

	float GetSigmaS() const { return m_sigma_s; }
	float GetSigmaR() const { return m_sigma_r; }

private:
	float m_sigma_s = float(10);
	float m_sigma_r = float(0.15);
};

}

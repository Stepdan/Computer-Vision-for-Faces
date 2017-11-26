#pragma once

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsDetailsEnhance.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectDetailsEnhance : virtual public IEffectOne
{
public:
	explicit EffectDetailsEnhance(const SettingsDetailsEnhance & settings = SettingsDetailsEnhance());
	~EffectDetailsEnhance() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	SettingsDetailsEnhance m_settings;
};

}

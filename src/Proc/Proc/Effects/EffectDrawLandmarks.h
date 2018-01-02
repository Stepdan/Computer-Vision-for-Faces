#pragma once

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsDrawLandmarks.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectDrawLandmarks : virtual public IEffectOne
{
public:
	explicit EffectDrawLandmarks(const SettingsDrawLandmarks & settings = SettingsDrawLandmarks());
	~EffectDrawLandmarks() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	SettingsDrawLandmarks m_settings;
};

}

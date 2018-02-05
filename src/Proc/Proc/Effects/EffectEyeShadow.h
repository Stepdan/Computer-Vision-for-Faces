#pragma once

#include "Types/Pointers.h"

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsEyeShadow.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectEyeShadow : virtual public IEffectOne
{
public:
	explicit EffectEyeShadow(const SettingsEyeShadow & settings = SettingsEyeShadow());
	~EffectEyeShadow() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	SettingsEyeShadow m_settings;
};

}

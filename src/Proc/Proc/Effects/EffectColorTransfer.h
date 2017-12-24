#pragma once

#include "Proc/Interfaces/IEffectTwo.h"

#include "Proc/Settings/SettingsColorTransfer.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectColorTransfer : virtual public IEffectTwo
{
public:
	explicit EffectColorTransfer(const SettingsColorTransfer & settings = SettingsColorTransfer());
	~EffectColorTransfer() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src0, const cv::Mat & src1, cv::Mat & dst) override;

private:
	SettingsColorTransfer m_settings;
};

}

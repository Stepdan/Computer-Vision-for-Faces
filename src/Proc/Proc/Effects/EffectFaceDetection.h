#pragma once

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsFaceDetection.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectFaceDetection : virtual public IEffectOne
{
public:
	explicit EffectFaceDetection(const SettingsFaceDetection & settings = SettingsFaceDetection());
	~EffectFaceDetection() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	SettingsFaceDetection m_settings;
};

}

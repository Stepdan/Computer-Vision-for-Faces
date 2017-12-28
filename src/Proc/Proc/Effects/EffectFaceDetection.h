#pragma once

#include "Types/Pointers.h"

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
	void Detect(const cv::Mat & src);
	void DrawLandmarks(const cv::Mat & src, cv::Mat & dst);

private:
	SettingsFaceDetection m_settings;

	SharedPtr<IEffectOne> m_effectDrawLandmarks;
};

}

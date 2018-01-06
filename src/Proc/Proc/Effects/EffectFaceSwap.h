#pragma once

#include "Types/Pointers.h"

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsFaceSwap.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectFaceSwap : virtual public IEffectOne
{
public:
	explicit EffectFaceSwap(const SettingsFaceSwap & settings = SettingsFaceSwap());
	~EffectFaceSwap() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	SettingsFaceSwap m_settings;

	SharedPtr<IEffectOne> m_faceDetector;
};

}

#include "EffectHelper.h"

#include "Proc/Settings/SettingsDetailsEnhance.h"

#include "Proc/Effects/EffectDetailsEnhance.h"

#include "Proc/Effects/Factory/EffectsFactory.h"

using namespace Proc;
using namespace Proc::Interfaces;

namespace VisionApp {

EffectHelper::EffectHelper(const SharedPtr<ImageHelper>& helper)
    : m_imageHelper(helper)
{
	EffectsFactory::Instance().Add<EffectDetailsEnhance>(SettingsDetailsEnhance::SETTINGS_ID, EffectInput::One);
}

void EffectHelper::ApplyEffect(const SharedPtr<Proc::BaseSettings>& settings)
{
    auto effect = EffectsFactory::Instance().CreateEffectOne(settings->GetSettingsID());
    effect->SetBaseSettings(*settings);

    cv::Mat dst;
    effect->Apply(m_imageHelper->GetCvMat(), dst);
    m_imageHelper->SetImage(dst);
}

}

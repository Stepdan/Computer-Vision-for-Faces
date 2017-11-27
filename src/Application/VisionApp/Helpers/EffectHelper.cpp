#include "EffectHelper.h"

#include "Proc/Settings/SettingsDetailsEnhance.h"

#include "Proc/Effects/EffectDetailsEnhance.h"

#include "Proc/Effects/Factory/EffectsFactory.h"

using namespace Proc;
using namespace Proc::Interfaces;

namespace VisionApp {

EffectHelper::EffectHelper()
{
	EffectsFactory::Instance().Add<EffectDetailsEnhance>(SettingsDetailsEnhance::SETTINGS_ID, EffectInput::One);
}

SharedPtr<IEffectOne> EffectHelper::CreateEffectOne(const Proc::BaseSettings & settings)
{
	return EffectsFactory::Instance().CreateEffectOne(settings.GetSettingsID());
}

SharedPtr<IEffectTwo> EffectHelper::CreateEffectTwo(const Proc::BaseSettings & settings)
{
	return EffectsFactory::Instance().CreateEffectTwo(settings.GetSettingsID());
}

}

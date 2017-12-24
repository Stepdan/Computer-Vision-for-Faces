#include "EffectHelper.h"

#include "Proc/Settings/SettingsColorTransfer.h"
#include "Proc/Settings/SettingsDetailsEnhance.h"
#include "Proc/Settings/SettingsFaceDetection.h"
#include "Proc/Settings/SettingsFilter.h"

#include "Proc/Effects/EffectColorTransfer.h"
#include "Proc/Effects/EffectDetailsEnhance.h"
#include "Proc/Effects/EffectFaceDetection.h"
#include "Proc/Effects/EffectFilter.h"

#include "Proc/Effects/Factory/EffectsFactory.h"

using namespace Proc;
using namespace Proc::Interfaces;

namespace VisionApp {

EffectHelper::EffectHelper(const SharedPtr<ImageHelper>& helper)
	: m_imageHelper(helper)
{
	EffectsFactory::Instance().AddEffectOne<EffectDetailsEnhance	>(SettingsDetailsEnhance	::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectFaceDetection		>(SettingsFaceDetection		::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectFilter			>(SettingsFilter			::SETTINGS_ID);

	EffectsFactory::Instance().AddEffectTwo<EffectColorTransfer		>(SettingsColorTransfer		::SETTINGS_ID);
}

void EffectHelper::ApplyEffect(const SharedPtr<Proc::BaseSettings>& settings)
{
	cv::Mat dst;
	switch(EffectsFactory::Instance().GetEffectInput(settings->GetSettingsID()))
	{
	case Proc::EffectInput::One:
		{
			auto effect = EffectsFactory::Instance().CreateEffectOne(settings->GetSettingsID());
			effect->SetBaseSettings(*settings);
			effect->Apply(m_imageHelper->GetCvMat(), dst);
		}
		break;
	case Proc::EffectInput::Two:
		{
			auto effect = EffectsFactory::Instance().CreateEffectTwo(settings->GetSettingsID());
			effect->SetBaseSettings(*settings);
			effect->Apply(m_imageHelper->GetCvMat(), m_imageHelper->GetCvMat2(), dst);
		}
		break;
	}

	m_imageHelper->SetImage(dst);
}

}

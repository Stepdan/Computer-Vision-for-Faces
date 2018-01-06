#include "EffectHelper.h"

#include "Proc/Effects/EffectColorTransfer.h"
#include "Proc/Effects/EffectDetailsEnhance.h"
#include "Proc/Effects/EffectDrawLandmarks.h"
#include "Proc/Effects/EffectFaceDetection.h"
#include "Proc/Effects/EffectFaceSwap.h"
#include "Proc/Effects/EffectFilter.h"

#include "Proc/Effects/Factory/EffectsFactory.h"

using namespace Proc;
using namespace Proc::Interfaces;

namespace VisionApp {

EffectHelper::EffectHelper(const SharedPtr<ImageHelper>& helper)
	: m_imageHelper(helper)
{
	EffectsFactory::Instance().AddEffectOne<EffectDetailsEnhance	>(SettingsDetailsEnhance	::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectDrawLandmarks		>(SettingsDrawLandmarks		::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectFaceDetection		>(SettingsFaceDetection		::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectFaceSwap			>(SettingsFaceSwap			::SETTINGS_ID);
	EffectsFactory::Instance().AddEffectOne<EffectFilter			>(SettingsFilter			::SETTINGS_ID);

	EffectsFactory::Instance().AddEffectTwo<EffectColorTransfer		>(SettingsColorTransfer		::SETTINGS_ID);
}

void EffectHelper::ApplyEffect(SharedPtr<Proc::BaseSettings> settings)
{
	cv::Mat dst;
	switch(EffectsFactory::Instance().GetEffectInput(settings->GetSettingsID()))
	{
	case Proc::EffectInput::One:
		{
			auto effect = EffectsFactory::Instance().CreateEffectOne(settings->GetSettingsID());
			effect->SetBaseSettings(*settings);
			effect->Apply(m_imageHelper->GetCvMat(), dst);

			if(settings->GetSettingsID() == "FaceDetection")
			{
				// @todo фуфуфу, но пока по другому нельзя передать в TrainingHelper
				const auto s = dynamic_cast<const Proc::SettingsFaceDetection&>(effect->GetBaseSettings());
				for(size_t i = 0; i < s.GetFacesCount(); ++i)
					std::dynamic_pointer_cast<Proc::SettingsFaceDetection>(settings)->AddFace(s.GetFace(i));
			}
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

	m_imageHelper->SetImage(dst, true);
}

}

#include "opencv2/photo.hpp"

#include "EffectDetailsEnhance.h"

namespace Proc {

EffectDetailsEnhance::EffectDetailsEnhance(const SettingsDetailsEnhance & settings/* = SettingsDetailsEnhance()*/)
	: m_settings(settings)
{
}

void EffectDetailsEnhance::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsDetailsEnhance &>(settings);
}

const BaseSettings & EffectDetailsEnhance::GetBaseSettings() const
{
	return m_settings;
}

void EffectDetailsEnhance::Apply(const cv::Mat & src, cv::Mat & dst)
{
	cv::detailEnhance(src, dst, m_settings.GetSigmaS(), m_settings.GetSigmaR());
}

}

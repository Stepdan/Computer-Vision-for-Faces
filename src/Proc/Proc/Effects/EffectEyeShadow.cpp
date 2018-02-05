#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"

#include <ctime>

#include "Types/Face.h"

#include "EffectEyeShadow.h"
#include "Proc/Utils/ProcUtils.h"

#include "Proc/Effects/Factory/EffectsFactory.h"
#include "Proc/Settings/SettingsFaceDetection.h"

namespace {

constexpr int PATTERN_SIZE = 256;

}

namespace Proc {

EffectEyeShadow::EffectEyeShadow(const SettingsEyeShadow & settings/* = SettingsEyeShadow()*/)
	: m_settings(settings)
{
}

void EffectEyeShadow::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsEyeShadow &>(settings);
}

const BaseSettings & EffectEyeShadow::GetBaseSettings() const
{
	return m_settings;
}

void EffectEyeShadow::Apply(const cv::Mat & src, cv::Mat & dst)
{
	// создаем паттерн теней
	// по сути является двумерным LUT
	cv::Mat shadowPattern(PATTERN_SIZE, PATTERN_SIZE, CV_8UC3);
	for(size_t i = 0; i < shadowPattern.cols; ++i)
		for(size_t j = 0; j < shadowPattern.rows; ++j)
		{
			shadowPattern.at<cv::Vec3b>(i, j)[0] = 255 - i;
			shadowPattern.at<cv::Vec3b>(i, j)[1] = 255 - i;
			shadowPattern.at<cv::Vec3b>(i, j)[2] = 255 - i;
		}

	cv::imwrite("C:/Projects/Computer_Vision_for_Faces/Images/TEMP/test.jpg", shadowPattern);

	const auto face = m_settings.GetFace();

}

}

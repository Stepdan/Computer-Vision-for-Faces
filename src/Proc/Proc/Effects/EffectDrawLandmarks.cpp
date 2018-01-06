#include "opencv2/opencv.hpp"

#include "Types/Face.h"

#include "EffectDrawLandmarks.h"

namespace Proc {

EffectDrawLandmarks::EffectDrawLandmarks(const SettingsDrawLandmarks & settings/* = SettingsDrawLandmarks()*/)
	: m_settings(settings)
{
}

void EffectDrawLandmarks::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsDrawLandmarks &>(settings);
}

const BaseSettings & EffectDrawLandmarks::GetBaseSettings() const
{
	return m_settings;
}

void EffectDrawLandmarks::Apply(const cv::Mat & src, cv::Mat & dst)
{
	dst = src.clone();

	// Рисуем frame
	const auto frame = m_settings.GetFace().GetFrame();
	cv::line(dst, cv::Point(frame.first.x, frame.first.y), cv::Point(frame.second.x, frame.first.y), cv::Scalar(255, 0, 0));
	cv::line(dst, cv::Point(frame.first.x, frame.second.y), cv::Point(frame.second.x, frame.second.y), cv::Scalar(255, 0, 0));
	cv::line(dst, cv::Point(frame.first.x, frame.first.y), cv::Point(frame.first.x, frame.second.y), cv::Scalar(255, 0, 0));
	cv::line(dst, cv::Point(frame.second.x, frame.first.y), cv::Point(frame.second.x, frame.second.y), cv::Scalar(255, 0, 0));

	const auto contour = m_settings.GetFace().GetAllPoints();
	for(const auto & point : contour)
	{
		// Считаем, что работаем в BGR24
		dst.at<cv::Vec3b>(point.y, point.x)[0] = 0;
		dst.at<cv::Vec3b>(point.y, point.x)[1] = 0;
		dst.at<cv::Vec3b>(point.y, point.x)[2] = 255;
	}
}

}

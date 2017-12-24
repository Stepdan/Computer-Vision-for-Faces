#include <opencv2/opencv.hpp>

#include "EffectColorTransfer.h"

namespace Proc {

EffectColorTransfer::EffectColorTransfer(const SettingsColorTransfer & settings/* = SettingsColorTransfer()*/)
	: m_settings(settings)
{
}

void EffectColorTransfer::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsColorTransfer &>(settings);
}

const BaseSettings & EffectColorTransfer::GetBaseSettings() const
{
	return m_settings;
}

void EffectColorTransfer::Apply(const cv::Mat & src0, const cv::Mat & src1, cv::Mat & dst)
{
	//create a copy of the destination
	dst = src0.clone();

	cv::Mat src0LAB, src1LAB, dstLAB;

	// Convert the images to Lab color space
	cv::cvtColor(src0, src0LAB, CV_BGR2Lab);
	cv::cvtColor(src1, src1LAB, CV_BGR2Lab);
	cv::cvtColor(dst , dstLAB , CV_BGR2Lab);

	// Convert to float32
	src0LAB.convertTo(src0LAB, CV_32F);
	src1LAB.convertTo(src1LAB, CV_32F);
	dstLAB .convertTo(dstLAB , CV_32F);

	// Create matrices to store the separated channels
	std::vector<cv::Mat> src0_channels(3), src1_channels(3), dst_channels(3);

	// Split the channels
	cv::split(src0LAB, src0_channels);
	cv::split(src1LAB, src1_channels);
	cv::split(dstLAB , dst_channels);

	float mean1, mean2, mean3, mean4, mean5, mean6;
	float stddev1, stddev2, stddev3, stddev4, stddev5, stddev6;
	cv::Scalar meanSrc0, meanSrc1, stdSrc0, stdSrc1;

	// Finding the mean and Std for different channels for srcLAB image
	cv::meanStdDev(src1LAB, meanSrc1, stdSrc1, cv::Mat());
	mean1 = meanSrc1.val[0];
	mean2 = meanSrc1.val[1];
	mean3 = meanSrc1.val[2];
	stddev1 = stdSrc1.val[0];
	stddev2 = stdSrc1.val[1];
	stddev3 = stdSrc1.val[2];

	// Finding the mean and Std for different channels for dstLAB image
	cv::meanStdDev(src0LAB, meanSrc0, stdSrc0, cv::Mat());
	mean4 = meanSrc0.val[0];
	mean5 = meanSrc0.val[1];
	mean6 = meanSrc0.val[2];
	stddev4 = stdSrc0.val[0];
	stddev5 = stdSrc0.val[1];
	stddev6 = stdSrc0.val[2];

	// Subtract the mean of destination image
	dst_channels[0] = src0_channels[0] - mean4;
	dst_channels[1] = src0_channels[1] - mean5;
	dst_channels[2] = src0_channels[2] - mean6;

	//scale the standard deviation of the destination image
	dst_channels[0] *= stddev4 / stddev1;
	dst_channels[1] *= stddev5 / stddev2;
	dst_channels[2] *= stddev6 / stddev3;

	// Add the mean of the source image to get the color
	dst_channels[0] = dst_channels[0] + mean1;
	dst_channels[1] = dst_channels[1] + mean2;
	dst_channels[2] = dst_channels[2] + mean3;

	// Merge the channels
	cv::merge(dst_channels, dstLAB);

	// Convert back from float32
	dstLAB.convertTo(dstLAB, CV_8UC3);

	// Convert the image to BGR color space
	cv::cvtColor(dstLAB, dst, CV_Lab2BGR);
}

}

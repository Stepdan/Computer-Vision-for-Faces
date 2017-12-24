#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>

#include "Proc/Utils/ProcUtils.h"

#include "EffectFilter.h"

namespace Proc {

void EffectFilter::Impl::Clarendon::Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings)
{
	dst = src.clone();

	//Enhance the channel for any image BGR or HSV etc
	float origin[] = {0, 28, 56, 85 , 113, 141, 170, 198, 227, 255};
	float rCurve[] = {0, 16, 35, 64 , 117, 163, 200, 222, 237, 249};
	float gCurve[] = {0, 24, 49, 98 , 141, 174, 201, 223, 239, 255};
	float bCurve[] = {0, 38, 66, 104, 139, 175, 206, 226, 245, 255};

	// Splitting the channels
	std::vector<cv::Mat> channels(3);
	cv::split(dst, channels);

	// Create a LookUp Table
	float fullRange[256];
	for(int i = 0; i < 256; ++i)
		fullRange[i]= static_cast<float>(i);

	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, bCurve, origin);

	// Apply mapping and check for underflow/overflow in Red Channel
	cv::LUT(channels[0], lookUpTable, channels[0]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, gCurve, origin);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[1], lookUpTable, channels[1]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, rCurve, origin);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[2], lookUpTable, channels[2]);

	// Merge the channels
	cv::merge(channels, dst);
}

void EffectFilter::Impl::Kelvin::Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings)
{
	dst = src.clone();

	//Enhance the channel for any image BGR or HSV etc
	// Specifying the x-axis for mapping
	float originalR[] = {0, 60, 110, 150, 235, 255};
	float originalG[] = {0, 68, 105, 190, 255};
	float originalB[] = {0, 88, 145, 185, 255};

	// Specifying the y-axis for mapping
	float rCurve[] = {0, 102, 185, 220, 245, 245};
	float gCurve[] = {0, 68, 120, 220, 255};
	float bCurve[] = {0, 12, 140, 212, 255};

	// Splitting the channels
	std::vector<cv::Mat> channels(3);
	cv::split(dst, channels);

	// Create a LookUp Table
	float fullRange[256];
	for(int i = 0; i < 256; ++i)
		fullRange[i]= static_cast<float>(i);

	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, bCurve, originalB);

	// Apply mapping and check for underflow/overflow in Red Channel
	cv::LUT(channels[0], lookUpTable, channels[0]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, gCurve, originalG);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[1], lookUpTable, channels[1]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut, fullRange, rCurve, originalR);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[2], lookUpTable, channels[2]);

	// Merge the channels
	cv::merge(channels, dst);
}

void EffectFilter::Impl::XProII::Apply(const cv::Mat & src, cv::Mat & dst,  const SettingsFilter& settings)
{
	dst = src.clone();
	//Enhance the channel for any image BGR or HSV etc
	// Applying a vignette with some radius
	Proc::Utils::ApplyVignette(dst, settings.GetVignetteScale());

	// Specifying the x-axis for mapping
	float originalR[] = {0, 42, 105, 148, 185, 255};
	float originalG[] = {0, 40, 85, 125, 165, 212, 255};
	float originalB[] = {0, 40, 82, 125, 170, 225, 255 };

	// Specifying the y-axis for mapping
	float rCurve[] = {0, 28, 100, 165, 215, 255 };
	float gCurve[] = {0, 25, 75, 135, 185, 230, 255 };
	float bCurve[] = {0, 38, 90, 125, 160, 210, 222};

	// Splitting the channels
	std::vector<cv::Mat> channels(3);
	cv::split(dst, channels);

	// Create a LookUp Table
	float fullRange[256];
	for(int i = 0; i < 256; ++i)
		fullRange[i]= static_cast<float>(i);

	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut,fullRange,bCurve,originalB);

	// Apply mapping and check for underflow/overflow in Red Channel
	cv::LUT(channels[0],lookUpTable,channels[0]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut,fullRange,gCurve,originalG);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[1],lookUpTable,channels[1]);

	// Apply interpolation and create look up table
	Proc::Utils::Interpolation(lut,fullRange,rCurve,originalR);

	// Apply mapping and check for underflow/overflow in Blue Channel
	cv::LUT(channels[2],lookUpTable,channels[2]);

	// Merge the channels
	cv::merge(channels, dst);

	// Adjusting the contrast a bit - just for fun!
	Proc::Utils::AdjustContrast(dst, 1.2);
}

void EffectFilter::Impl::Cartoon::Apply(const cv::Mat & src, cv::Mat & dst,  const SettingsFilter& settings)
{
	// Make a copy of the origianl image to work with
	dst = src.clone();

	// Convert image to grayscale
	cv::Mat imgGray;
	cv::cvtColor(dst, imgGray, cv::COLOR_BGR2GRAY);

	// Apply Gaussian filter to the grayscale image
	cv::GaussianBlur(imgGray, imgGray, cv::Size(3,3), 0);

	// Detect edges in the image and threshold it
	cv::Mat edges, edgeMask;

	// parameters for laplacian operator
	int kernel_size = 5;
	int scale = 1;
	int ddepth = CV_8U;

	cv::Laplacian( imgGray, edges, ddepth, kernel_size, scale );
	cv::convertScaleAbs(edges, edges);
	edges = 255 - edges;
	cv::threshold(edges, edgeMask,150, 255, cv::THRESH_BINARY);

	// Create the highly blurred image using edge preserving filter
	cv::Mat imgBilateral;
	cv::edgePreservingFilter(dst, imgBilateral, 2, 50, 0.4);

	// Create a output Matrix
	cv::Mat output;
	output = cv::Scalar::all(0);

	// Combine the cartoon and edges
	cv::bitwise_and(imgBilateral, imgBilateral, output, edgeMask);

	dst = output;
}

//------------------------------------------------------------------------------------

EffectFilter::EffectFilter(const SettingsFilter & settings/* = SettingsFilter()*/)
	: m_settings(settings)
{
}

void EffectFilter::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsFilter &>(settings);

	switch(m_settings.GetFilterType())
	{
	case SettingsFilter::FilterType::Clarendon:
		Impl::Ptr(new Impl::Clarendon).swap(m_impl);
		break;
	case SettingsFilter::FilterType::Kelvin:
		Impl::Ptr(new Impl::Kelvin).swap(m_impl);
		break;
	case SettingsFilter::FilterType::XProII:
		Impl::Ptr(new Impl::XProII).swap(m_impl);
		break;
	case SettingsFilter::FilterType::Cartoon:
		Impl::Ptr(new Impl::Cartoon).swap(m_impl);
		break;
	}
}

const BaseSettings & EffectFilter::GetBaseSettings() const
{
	return m_settings;
}

void EffectFilter::Apply(const cv::Mat & src, cv::Mat & dst)
{
	m_impl->Apply(src, dst, m_settings);
}

}

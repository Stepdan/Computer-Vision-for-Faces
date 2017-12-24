#include "ProcUtils.h"

namespace Proc { namespace Utils {

void Interpolation(unsigned char* lut, float* fullRange, float* Curve, float* originalValue)
{
	int i;
	for (i=0; i < 256; ++i)
	{
		int j = 0;
		float a = fullRange[i];
		while(a > originalValue[j])
		{
			++j;
		}
		if (a == originalValue[j])
		{
			lut[i] = Curve[j];
			continue;
		}
		float slope = ((float)(Curve[j] - Curve[j-1]))/(originalValue[j] - originalValue[j-1]);
		float constant = Curve[j] - slope * originalValue[j];
		lut[i] = slope * fullRange[i] + constant;
	}
}

void ApplyVignette(cv::Mat& img, float vignetteScale)
{
	// convert to float
	// img = np.float32(img)
	int rows = img.rows;
	int cols = img.cols;

	// Compute the kernel size from the image dimensions
	int k = std::min(rows, cols) / vignetteScale;

	// Create a kernel to get the halo effect
	cv::Mat kernelX = cv::getGaussianKernel(cols,k);
	cv::Mat kernelY = cv::getGaussianKernel(rows,k);

	cv::Mat kernelX_Transpose;
	cv::transpose(kernelX, kernelX_Transpose);
	cv::Mat kernel = kernelY * kernelX_Transpose;

	// Normalize the kernel
	cv::Mat mask;
	cv::normalize(kernel, mask, 0, 1, cv::NORM_MINMAX);

	// Convert to float32
	img.convertTo(img,CV_32F);
	mask.convertTo(mask,CV_32F);

	// Split the channels
	std::vector<cv::Mat> channels(3);
	cv::split(img, channels);

	//Apply the halo all the channels of the image
	channels[0] += channels[0].mul(mask);
	channels[1] += channels[1].mul(mask);
	channels[2] += channels[2].mul(mask);

	// Merge the channels
	cv::merge(channels, img);
	img = img / 2;

	// Clipping operation performed to limit pixel values between 0 and 255
	cv::min(img, 255, img);
	cv::max(img, 0, img);

	// Convert back from float32
	img.convertTo(img, CV_8UC3);
}

void AdjustContrast(cv::Mat& img, float alpha)
{
	cv::Mat ycbImage;
	// Convert to YCrCb color space
	cv::cvtColor(img, ycbImage, cv::COLOR_BGR2YCrCb);
	// Convert to float32
	ycbImage.convertTo(ycbImage, CV_32F);
	std::vector<cv::Mat>channels(3);
	// Split the channels
	cv::split(ycbImage, channels);

	// Scale the Ychannel
	channels[0] = channels[0] * alpha;
	// Clipping operation performed to limit pixel values between 0 and 255
	cv::min(channels[0], 255, channels[0]);
	cv::max(channels[0], 0, channels[0]);

	// Merge the channels
	cv::merge(channels, ycbImage);

	// Convert back from float32
	ycbImage.convertTo(ycbImage, CV_8UC3);

	cv::Mat contrastImage;
	// Convert back to BGR
	cv::cvtColor(ycbImage, contrastImage, cv::COLOR_YCrCb2BGR);

	img = contrastImage;
}

}}

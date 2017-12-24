#pragma once

#include "opencv2/photo.hpp"

namespace Proc { namespace Utils {

void Interpolation(unsigned char* lut, float* fullRange, float* Curve, float* originalValue);

void ApplyVignette(cv::Mat& image, float vignetteScale);

void AdjustContrast(cv::Mat& image, float alpha);

}}

#pragma once

#include "opencv2/imgproc/imgproc.hpp"

#include "IEffect.h"

namespace Proc {

class IEffectOne : virtual public IEffect
{
protected:
	virtual ~IEffectOne() = default;

public:
	virtual void Apply(const cv::Mat & src1, const cv::Mat & src2, const cv::Mat & dst);
};

}

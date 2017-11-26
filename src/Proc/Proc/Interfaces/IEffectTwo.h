#pragma once

#include "opencv2/imgproc/imgproc.hpp"

#include "IEffect.h"

namespace Proc { namespace Interfaces {

class IEffectTwo : virtual public IEffect
{
protected:
	virtual ~IEffectTwo() = default;

public:
	virtual void Apply(const cv::Mat & src1, const cv::Mat & src2, cv::Mat & dst) = 0;
};

}}

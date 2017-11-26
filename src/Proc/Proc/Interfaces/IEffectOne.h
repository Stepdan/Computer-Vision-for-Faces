#pragma once

#include "opencv2/imgproc/imgproc.hpp"

#include "IEffect.h"

namespace Proc { namespace Interfaces {

class IEffectOne : virtual public IEffect
{
protected:
	virtual ~IEffectOne() = default;

public:
	virtual void Apply(const cv::Mat & src, cv::Mat & dst) = 0;
};

}}

#pragma once

#include <string>

#include "Types/Pointers.h"

#include "Core/CoreTypes/ColorSpaces.h"
#include "Core/CoreTypes/FrameInfo.h"

namespace Core {

enum class ImageImpl
{
	OpenCV,
	Qt
};

enum class FlipOrientation
{
	Default = -2,
	// Совпадает со значениями из OpenCV
	Diagonal   = -1,
	Vertical   = 0,
	Horizontal = 1
};

}

namespace Core { namespace Interfaces {

class IDataImage
{
public:
	virtual ~IDataImage() = default;

public:
    virtual SharedPtr<IDataImage> Clone()                          = 0;
    virtual ImageImpl             GetImpl() const                  = 0;
    virtual SharedPtr<IDataImage> ChangeImpl()                     = 0;
    virtual void                  ColorSpaceConvert(ColorSpace cs) = 0;
	virtual FrameInfo             GetFrameInfo()                   = 0;
	virtual SharedPtr<IDataImage> Subframe(int x0, int y0, int width, int height) = 0;
	virtual SharedPtr<IDataImage> Flip(FlipOrientation) = 0;
	virtual void                  Save(const std::string & pathname, const std::string & extension) = 0;
};

}}

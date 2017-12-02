#pragma once

#include "Types/Pointers.h"

#include "Core/CoreTypes/ColorSpaces.h"
#include "Core/CoreTypes/FrameInfo.h"

namespace Core {

enum class ImageImpl
{
	OpenCV,
	Qt
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
    virtual const FrameInfo&      GetFrameInfo()                   = 0;
};

}}

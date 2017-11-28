#pragma once

#include "Types/Pointers.h"

#include "Core/Interfaces/IDataImage.h"

#include "Proc/Interfaces/IEffectOne.h"
#include "Proc/Interfaces/IEffectTwo.h"
#include "Proc/Settings/BaseSettings.h"

#include "ImageHelper.h"

using namespace Core::Interfaces;
using namespace Proc::Interfaces;

namespace VisionApp {

class EffectHelper
{
public:
    EffectHelper(const SharedPtr<ImageHelper>&);
	~EffectHelper() = default;

public:
    void ApplyEffect(const SharedPtr<Proc::BaseSettings>&);

private:
    SharedPtr<ImageHelper> m_imageHelper;
};

}

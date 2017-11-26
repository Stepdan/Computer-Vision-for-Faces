#pragma once

#include "Types/Pointers.h"

#include "Proc/Interfaces/IEffectOne.h"
#include "Proc/Interfaces/IEffectTwo.h"
#include "Proc/Settings/BaseSettings.h"

using namespace Proc::Interfaces;

namespace VisionApp {

class EffectHelper
{
public:
	EffectHelper();
	~EffectHelper() = default;

public:
	SharedPtr<IEffectOne> CreateEffectOne(const Proc::BaseSettings & settings);
	SharedPtr<IEffectTwo> CreateEffectTwo(const Proc::BaseSettings & settings);
};

}

#pragma once

#include "Proc/Settings/BaseSettings.h"

namespace Proc{

enum class EffectInput { One, Two };

}

namespace Proc { namespace Interfaces {

class IEffect
{
public:
	virtual ~IEffect() = default;

	virtual const BaseSettings & GetBaseSettings() const = 0;
	virtual void SetBaseSettings(const BaseSettings & settings) = 0;
};

}}

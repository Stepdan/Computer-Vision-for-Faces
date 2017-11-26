#pragma once

#include "Proc/Settings/BaseSettings.h"

namespace Proc {

class IEffect
{
public:
	virtual ~IEffect() = default;

	virtual const BaseSettings & GetBaseSettings() const;
	virtual void SetBaseSettings(const BaseSettings & settings);
};

}

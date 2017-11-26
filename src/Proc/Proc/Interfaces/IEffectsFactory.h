#pragma once

#include "Types/Pointers.h"

#include "Proc/Interfaces/IEffectOne.h"
#include "Proc/Interfaces/IEffectTwo.h"

namespace Proc { namespace Interfaces {

class ICreatorOne
{
public:
	ICreatorOne() = default;
	virtual SharedPtr<IEffectOne> Create() const = 0;
};

class ICreatorTwo
{
public:
	ICreatorTwo() = default;
	virtual SharedPtr<IEffectTwo> Create() const = 0;
};

class IEffectsFactory
{
public:
	virtual ~IEffectsFactory() = default;

	virtual SharedPtr<IEffectOne> CreateEffectOne(const std::string & settingsID) const = 0;

	virtual SharedPtr<IEffectTwo> CreateEffectTwo(const std::string & settingsID) const = 0;
};

}}

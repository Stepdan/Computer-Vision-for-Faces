#pragma once

#include <map>

#include "Proc/Interfaces/IEffectsFactory.h"

using namespace Proc::Interfaces;

namespace Proc {

template<class T>
class CreatorEffectOne : public ICreatorOne
{
public:
	SharedPtr<IEffectOne> Create() const
	{
		SharedPtr<IEffectOne> effect(new T());
		return effect;
	}
};

template<class T>
class CreatorEffectTwo : public ICreatorTwo
{
public:
	SharedPtr<IEffectTwo> Create() const
	{
		SharedPtr<IEffectTwo> effect(new T());
		return effect;
	}
};

class EffectsFactory : public IEffectsFactory
{
public:
	static EffectsFactory & Instance();

	SharedPtr<IEffectOne> CreateEffectOne(const std::string & settingsID) const;
	SharedPtr<IEffectTwo> CreateEffectTwo(const std::string & settingsID) const;

	template<class T>
	void EffectsFactory::Add(const std::string & settingsID, EffectInput in)
	{
		switch(in)
		{
		case EffectInput::One:
			if(m_creatorsEffectsOne.find(settingsID) == m_creatorsEffectsOne.end())
				m_creatorsEffectsOne[settingsID] = new CreatorEffectOne<T>();
			break;
		case EffectInput::Two:
//			if(m_creatorsEffectsTwo.find(settingsID) == m_creatorsEffectsTwo.end())
//				m_creatorsEffectsTwo[settingsID] = new CreatorEffectTwo<T>();
			break;
		}
	}

private:
	EffectsFactory() = default;
	EffectsFactory(const EffectsFactory&);
	EffectsFactory& operator=(EffectsFactory&);
	~EffectsFactory() = default;

private:
	std::map<std::string, ICreatorOne*> m_creatorsEffectsOne;
	std::map<std::string, ICreatorTwo*> m_creatorsEffectsTwo;
};

}

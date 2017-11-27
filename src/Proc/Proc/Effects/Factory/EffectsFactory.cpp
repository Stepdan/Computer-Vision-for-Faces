#include "EffectsFactory.h"

#include <cassert>

using namespace Proc::Interfaces;

using CreatorsOneMap = std::map<std::string, ICreatorOne*>;
using CreatorsTwoMap = std::map<std::string, ICreatorTwo*>;

namespace Proc {

EffectsFactory& EffectsFactory::Instance()
{
	static EffectsFactory obj;
	return obj;
}

SharedPtr<IEffectOne> EffectsFactory::CreateEffectOne(const std::string & settingsID) const
{
	const auto it = m_creatorsEffectsOne.find(settingsID);

	if(it == m_creatorsEffectsOne.end())
		assert(0 && "EffectsFactory::CreateEffectOne: Incorrect settingsID!");

	return it->second->Create();
}

SharedPtr<IEffectTwo> EffectsFactory::CreateEffectTwo(const std::string & settingsID) const
{
	const auto it = m_creatorsEffectsTwo.find(settingsID);

	if(it == m_creatorsEffectsTwo.end())
		assert(0 && "EffectsFactory::CreateEffectOne: Incorrect settingsID!");

	return it->second->Create();
}



}

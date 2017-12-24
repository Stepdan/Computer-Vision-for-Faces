#pragma once

#include <string>

namespace Proc {

class BaseSettings
{
public:
	virtual ~BaseSettings() = default;
	virtual const std::string & GetSettingsID() const = 0;

protected:
	BaseSettings() = default;
};

#define PROC_SETTINGS(SettingsID) \
	static const std::string SETTINGS_ID;\
	const std::string & GetSettingsID() const { return SETTINGS_ID; }

}

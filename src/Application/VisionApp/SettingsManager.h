#pragma once

#include <QSettings>

#include "Types/Pointers.h"

namespace VisionApp {

class SettingsManager : public QSettings
{
public:
	static SettingsManager & Instance();

private:
	SettingsManager();
	SettingsManager(const SettingsManager&) = delete;
	SettingsManager& operator=(const SettingsManager&) = delete;
	~SettingsManager() = default;
};

}

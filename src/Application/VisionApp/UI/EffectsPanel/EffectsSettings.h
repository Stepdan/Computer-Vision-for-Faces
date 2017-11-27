#pragma once

#include <QBoxLayout>

#include "Types/Pointers.h"
#include "Proc/Settings/BaseSettings.h"

namespace VisionApp { namespace EffectsSettings {

using SettingsCreator = SharedPtr<Proc::BaseSettings>(*)(QBoxLayout*);
using SettingsCreatorList = std::vector<std::pair<QString, SettingsCreator>>;
const SettingsCreatorList& GetSettingsCreatorList();

}}

#include "SettingsManager.h"

namespace
{
const QString COMPANY_NAME = "StepCo";
const QString PRODUCT_NAME = "VisionApp";
}

namespace VisionApp {

SettingsManager& SettingsManager::Instance()
{
	static SettingsManager obj;
	return obj;
}

// private
SettingsManager::SettingsManager()
	: QSettings(COMPANY_NAME, PRODUCT_NAME)
{
}

}

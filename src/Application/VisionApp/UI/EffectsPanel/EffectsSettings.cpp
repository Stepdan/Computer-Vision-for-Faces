#include "EffectsSettings.h"

#include "IntFieldSpinBox.h"
#include "DoubleFieldSpinBox.h"

#include "Proc/Settings/BaseSettings.h"
#include "Proc/Settings/SettingsDetailsEnhance.h"
#include "Proc/Settings/SettingsFaceDetection.h"

namespace VisionApp { namespace EffectsSettings {

namespace {

template <typename T>
IntFieldSpinBox* CreateIntFieldSpinBox(QBoxLayout *layout, const QString &name, int value, T t)
{
	auto *field = new IntFieldSpinBox();

	field->setObjectName(name + "EffectsPanelIntField");
	field->SetName(name);
	field->SetValue(value);

	layout->addWidget(field);

	QObject::connect(field, &IntFieldSpinBox::valueChanged, [t, field]() { t(field->GetValue()); });

	return field;
}

//----------------------------------------------------------

template <typename T>
DoubleFieldSpinBox* CreateDoubleFieldSpinBox(QBoxLayout *layout, const QString &name, double value, T t)
{
	auto *field = new DoubleFieldSpinBox();

	field->setObjectName(name + "EffectsPanelDoubleField");
	field->SetName(name);
	field->SetValue(value);

	layout->addWidget(field);

	QObject::connect(field, &DoubleFieldSpinBox::valueChanged, [t, field]() { t(field->GetValue()); });

	return field;
}

//----------------------------------------------------------

template <typename T>
SharedPtr<T> GreateSettings()
{
	SharedPtr<T> settings(new T());
	return settings;
}

//----------------------------------------------------------

SharedPtr<Proc::BaseSettings> SettingsDetailsEnhance(QBoxLayout *layout)
{
	auto settings = GreateSettings<Proc::SettingsDetailsEnhance>();

	CreateIntFieldSpinBox(layout, "SigmaS", settings->GetSigmaS(), [settings](int value){
		settings->SetSigmaS(value);
	});

	CreateDoubleFieldSpinBox(layout, "SigmaR", settings->GetSigmaR(), [settings](double value){
		settings->SetSigmaR(value);
	});

	return settings;
}

//----------------------------------------------------------

SharedPtr<Proc::BaseSettings> SettingsFaceDetection(QBoxLayout *layout)
{
	auto settings = GreateSettings<Proc::SettingsFaceDetection>();

	return settings;
}

}

const SettingsCreatorList g_settingsCreator {
	{ "DetailsEnhance", &SettingsDetailsEnhance },
	{ "FaceDetection", &SettingsFaceDetection }
};

const SettingsCreatorList& GetSettingsCreatorList()
{
	return g_settingsCreator;
}

}}

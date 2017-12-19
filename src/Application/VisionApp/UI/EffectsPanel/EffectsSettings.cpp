#include "EffectsSettings.h"

#include <QRadioButton>
#include <QGroupBox>

#include "IntFieldSpinBox.h"
#include "DoubleFieldSpinBox.h"

#include "Proc/Settings/BaseSettings.h"
#include "Proc/Settings/SettingsDetailsEnhance.h"
#include "Proc/Settings/SettingsFaceDetection.h"
#include "Proc/Settings/SettingsFilter.h"

namespace VisionApp { namespace EffectsSettings {

namespace {

template <typename T>
void CreateIntFieldSpinBox(QBoxLayout *layout, const QString &name, int value, T t)
{
	auto *field = new IntFieldSpinBox();

	field->setObjectName(name + "EffectsPanelIntField");
	field->SetName(name);
	field->SetValue(value);

	layout->addWidget(field);

	QObject::connect(field, &IntFieldSpinBox::valueChanged, [t, field]() { t(field->GetValue()); });
}

//----------------------------------------------------------

template <typename T>
void CreateDoubleFieldSpinBox(QBoxLayout *layout, const QString &name, double value, T t)
{
	auto *field = new DoubleFieldSpinBox();

	field->setObjectName(name + "EffectsPanelDoubleField");
	field->SetName(name);
	field->SetValue(value);

	layout->addWidget(field);

	QObject::connect(field, &DoubleFieldSpinBox::valueChanged, [t, field]() { t(field->GetValue()); });
}

//----------------------------------------------------------

template <typename T>
void CreateRadio(QBoxLayout *layout, const QString &name, const std::vector<QString> &names, int minValue, int value, T t)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	for (size_t i = 0, sz = names.size(); i < sz; ++i)
	{
		auto *button = new QRadioButton(names[i]);
		if (static_cast<int>(i) == value - minValue)
			button->setChecked(true);

		QObject::connect(button, &QRadioButton::toggled, [t, minValue, i](bool checked) {if (checked) t(minValue + static_cast<int>(i)); });
		vbox->addWidget(button);
	}

	auto *group = new QGroupBox(name);
	group->setLayout(vbox);
	layout->addWidget(group);
}

//----------------------------------------------------------

template <typename T>
SharedPtr<T> CreateSettings()
{
	SharedPtr<T> settings(new T());
	return settings;
}

//----------------------------------------------------------

SharedPtr<Proc::BaseSettings> SettingsDetailsEnhance(QBoxLayout *layout)
{
	auto settings = CreateSettings<Proc::SettingsDetailsEnhance>();

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
	auto settings = CreateSettings<Proc::SettingsFaceDetection>();

	return settings;
}

//----------------------------------------------------------

SharedPtr<Proc::BaseSettings> SettingsFilter(QBoxLayout *layout)
{
	auto settings = CreateSettings<Proc::SettingsFilter>();

	CreateRadio(layout, "Filter", { "Clarendon", "Kelvin", "Moon", "XProII", "PencilSketch", "Cartoon" },
		static_cast<int>(Proc::SettingsFilter::FilterType::Clarendon),
		static_cast<int>(settings->GetFilterType()),
		[settings](int value) {settings->SetFilterType(static_cast<Proc::SettingsFilter::FilterType>(value));
	});

	CreateDoubleFieldSpinBox(layout, "Vignette scale", settings->GetVignetteScale(), [settings](double value){
		settings->SetVignetteScale(value);
	});

	return settings;
}

}

const SettingsCreatorList g_settingsCreator {
	{ "DetailsEnhance", &SettingsDetailsEnhance },
	{ "FaceDetection", &SettingsFaceDetection },
	{ "Filter", &SettingsFilter }
};

const SettingsCreatorList& GetSettingsCreatorList()
{
	return g_settingsCreator;
}

}}

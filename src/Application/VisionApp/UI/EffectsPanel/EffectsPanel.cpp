#include "EffectsPanel.h"
#include "ui_EffectsPanel.h"

#include <cassert>

#include <QObject>
#include <QSlider>
#include <QBoxLayout>

#include "Types/Pointers.h"

#include "Proc/Effects/Factory/EffectsFactory.h"
#include "Proc/Settings/BaseSettings.h"

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "EffectsSettings.h"

using namespace VisionApp::EffectsSettings;

namespace {

void ClearLayout(QLayout *layout)
{
	if(!layout)
		return;

	QLayoutItem* item;
	while((item = layout->takeAt(0)))
	{
		if (item->layout())
			ClearLayout(item->layout());
		else if (item->widget())
			delete item->widget();

		delete item;
	}
}

}

EffectsPanel::EffectsPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EffectsPanel)
{
	ui->setupUi(this);

	ui->comboBox->addItem("");
	for(const auto & item : GetSettingsCreatorList())
		ui->comboBox->addItem(item.first);

	connect(ui->comboBox, (void (QComboBox::*)(int))&QComboBox::currentIndexChanged, this, &EffectsPanel::OnEffectChanged);
	connect(ui->okButton, &QAbstractButton::clicked, this, [this](){ emit effectApplyed(m_settings); });
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::EFFECT_APPLYED, this, SIGNAL(effectApplyed(const SharedPtr<Proc::BaseSettings>&)));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::EFFECT_CANCELED, ui->cancelButton, SIGNAL(clicked()));
}

EffectsPanel::~EffectsPanel()
{
	delete ui;
}

void EffectsPanel::OnEffectChanged(int index)
{
	if(index < 0) return;

	auto layout = ui->scrollAreaContent->layout();
	ClearLayout(layout);
	auto settings = GetSettingsCreatorList()[index-1].second(qobject_cast<QBoxLayout*>(layout));
	qobject_cast<QBoxLayout*>(ui->scrollAreaContent->layout())->addStretch();

	m_settings = settings;
}

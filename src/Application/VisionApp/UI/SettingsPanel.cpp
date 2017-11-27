#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"

#include <QAbstractButton>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

SettingsPanel::SettingsPanel(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::SettingsPanel)
	, m_effectsPanel(new EffectsPanel(this))
{
	ui->setupUi(this);

	ui->stackedWidget->addWidget(m_effectsPanel);

	ui->stackedWidget->setCurrentWidget(m_effectsPanel);

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::EFFECTS_CLICKED, this, SLOT(OnEffectsClicked()));
}

SettingsPanel::~SettingsPanel()
{
	delete ui;
}

void SettingsPanel::OnEffectsClicked()
{
	ui->stackedWidget->setCurrentWidget(m_effectsPanel);
}

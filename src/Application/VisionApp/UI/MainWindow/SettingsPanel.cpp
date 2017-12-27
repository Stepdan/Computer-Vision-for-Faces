#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"

#include <QAbstractButton>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

SettingsPanel::SettingsPanel(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::SettingsPanel)
	, m_effectsPanel(new EffectsPanel(this))
	, m_capturePanel(new CapturePanel(this))
	, m_trainingPanel(new TrainingPanel(this))
{
	ui->setupUi(this);

	ui->stackedWidget->addWidget(m_effectsPanel);
	ui->stackedWidget->addWidget(m_capturePanel);
	ui->stackedWidget->addWidget(m_trainingPanel);

	ui->stackedWidget->setCurrentWidget(m_effectsPanel);

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::EFFECTS_CLICKED, this, SLOT(OnEffectsClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::CAPTURE_CLICKED, this, SLOT(OnCaptureClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_CLICKED, this, SLOT(OnTrainingClicked()));
}

SettingsPanel::~SettingsPanel()
{
	delete ui;
}

void SettingsPanel::OnEffectsClicked()
{
	ui->stackedWidget->setCurrentWidget(m_effectsPanel);
}

void SettingsPanel::OnCaptureClicked()
{
	ui->stackedWidget->setCurrentWidget(m_capturePanel);
}

void SettingsPanel::OnTrainingClicked()
{
	ui->stackedWidget->setCurrentWidget(m_trainingPanel);
}

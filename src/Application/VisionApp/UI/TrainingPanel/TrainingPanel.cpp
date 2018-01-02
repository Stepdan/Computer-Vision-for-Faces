#include "TrainingPanel.h"
#include "ui_TrainingPanel.h"

#include <QAbstractButton>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "LandmarkPreferenceDialog.h"

TrainingPanel::TrainingPanel(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TrainingPanel)
	, m_landmarkFileSettings(new LandmarkFileSettings())
{
	ui->setupUi(this);

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_FACE_DETECT_CLICKED, ui->faceDetectButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_CANCEL_CLICKED, ui->cancelButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_SAVE_LANDMARKS_CLICKED, ui->saveLandmarksButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_LANDMARK_FILE_SETTINGS_CHANGED, this, SIGNAL(landmarkFileSettingsChanged(const SharedPtr<LandmarkFileSettings> &)));

	connect(ui->settingsButton, &QAbstractButton::clicked, this, &TrainingPanel::OnSettingsClicked);
}

TrainingPanel::~TrainingPanel()
{
	delete ui;
}

void TrainingPanel::OnFaceDetectClicked()
{

}

void TrainingPanel::OnSettingsClicked()
{
	LandmarkPreferenceDialog dlg(m_landmarkFileSettings, this);
	dlg.exec();
	emit landmarkFileSettingsChanged(m_landmarkFileSettings);
}

void TrainingPanel::OnSaveLandmarksClicked()
{

}

#include "TrainingPanel.h"
#include "ui_TrainingPanel.h"

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

TrainingPanel::TrainingPanel(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TrainingPanel)
{
	ui->setupUi(this);

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_FACE_DETECT_CLICKED, ui->faceDetectButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_CANCEL_CLICKED, ui->cancelButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_SAVE_LANDMARKS_CLICKED, ui->saveLandmarksButton, SIGNAL(clicked()));
}

TrainingPanel::~TrainingPanel()
{
	delete ui;
}

void TrainingPanel::OnFaceDetectClicked()
{

}

void TrainingPanel::OnFolderClicked()
{

}

void TrainingPanel::OnSaveLandmarksClicked()
{

}

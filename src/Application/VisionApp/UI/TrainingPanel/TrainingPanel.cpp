#include "TrainingPanel.h"
#include "ui_TrainingPanel.h"

TrainingPanel::TrainingPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TrainingPanel)
{
	ui->setupUi(this);
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

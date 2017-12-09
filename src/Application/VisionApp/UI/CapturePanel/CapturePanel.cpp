#include "CapturePanel.h"
#include "ui_CapturePanel.h"

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

CapturePanel::CapturePanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CapturePanel)
{
	ui->setupUi(this);

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::CAPTURE_STARTED, ui->startButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::CAPTURE_CANCELED, ui->stopButton, SIGNAL(clicked()));
}

CapturePanel::~CapturePanel()
{
	delete ui;
}

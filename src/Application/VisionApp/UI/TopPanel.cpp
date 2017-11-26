#include "TopPanel.h"
#include "ui_TopPanel.h"

#include <QAbstractButton>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

TopPanel::TopPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TopPanel)
{
	ui->setupUi(this);

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::LOAD_IMAGE, ui->loadButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::SAVE_IMAGE, ui->saveButton, SIGNAL(clicked()));
}

TopPanel::~TopPanel()
{
	delete ui;
}

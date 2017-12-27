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
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::LOAD_IMAGE2, ui->load2Button, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::SAVE_IMAGE, ui->saveButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::UNDO, ui->undoButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::REDO, ui->redoButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::RESET, ui->resetButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::COMPARE_PRESSED, ui->compareButton, SIGNAL(pressed()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::COMPARE_RELEASED, ui->compareButton, SIGNAL(released()));

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::EFFECTS_CLICKED, ui->effectsButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::CAPTURE_CLICKED, ui->captureButton, SIGNAL(clicked()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_CLICKED, ui->trainingButton, SIGNAL(clicked()));
}

TopPanel::~TopPanel()
{
	delete ui;
}

void TopPanel::SetUndoEnabled(bool enabled)
{
	ui->undoButton->setEnabled(enabled);
}

void TopPanel::SetRedoEnabled(bool enabled)
{
	ui->redoButton->setEnabled(enabled);
}

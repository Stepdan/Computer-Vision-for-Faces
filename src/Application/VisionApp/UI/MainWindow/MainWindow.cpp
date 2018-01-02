#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::UPDATE_INFO_TEXT, this, SLOT(OnUpdateInfoText(const QString &)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::SetImage(const QImage & image)
{
	ui->scene->SetImage(image);
}

void MainWindow::UpdateStateUndoButtons(bool undoEnabled, bool redoEnabled)
{
	ui->topPanel->SetUndoEnabled(undoEnabled);
	ui->topPanel->SetRedoEnabled(redoEnabled);
}

void MainWindow::UpdateImageInfoText(const QString & text)
{
	m_imageInfo = text;
	ui->bottomPanel->SetText(m_imageInfo);
}

void MainWindow::OnUpdateInfoText(const QString & text)
{
	ui->bottomPanel->SetText(m_imageInfo + "\n" + text);
}

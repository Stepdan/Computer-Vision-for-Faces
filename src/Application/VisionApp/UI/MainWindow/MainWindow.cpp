#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
	ui->bottomPanel->SetText(text);
}

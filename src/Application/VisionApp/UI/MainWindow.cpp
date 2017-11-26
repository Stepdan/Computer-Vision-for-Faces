#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->settingsPanel, &SettingsPanel::click, this, &MainWindow::applyEffect);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::SetImage(const QImage & image)
{
	ui->scene->SetImage(image);
}

QPixmap MainWindow::GetImage() const
{
	return ui->scene->GetImage();
}

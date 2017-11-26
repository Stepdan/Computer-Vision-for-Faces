#include "BottomPanel.h"
#include "ui_BottomPanel.h"

BottomPanel::BottomPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BottomPanel)
{
	ui->setupUi(this);
}

BottomPanel::~BottomPanel()
{
	delete ui;
}

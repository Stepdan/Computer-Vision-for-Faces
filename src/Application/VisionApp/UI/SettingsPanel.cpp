#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"

SettingsPanel::SettingsPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SettingsPanel)
{
	ui->setupUi(this);
}

SettingsPanel::~SettingsPanel()
{
	delete ui;
}

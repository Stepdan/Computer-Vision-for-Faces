#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"

#include <QAbstractButton>

SettingsPanel::SettingsPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SettingsPanel)
{
	ui->setupUi(this);

	connect(ui->pushButton, &QAbstractButton::clicked, this, &SettingsPanel::click);
}

SettingsPanel::~SettingsPanel()
{
	delete ui;
}

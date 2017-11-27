#include "IntFieldSpinBox.h"
#include "ui_IntFieldSpinBox.h"

IntFieldSpinBox::IntFieldSpinBox(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IntFieldSpinBox)
{
	ui->setupUi(this);

	connect(ui->spinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &IntFieldSpinBox::valueChanged);
}

IntFieldSpinBox::~IntFieldSpinBox()
{
	delete ui;
}


void IntFieldSpinBox::SetName(const QString & str)
{
	ui->label->setText(str);
}

void IntFieldSpinBox::SetValue(int value)
{
	ui->spinBox->setValue(value);
}

double IntFieldSpinBox::GetValue() const
{
	return ui->spinBox->value();
}

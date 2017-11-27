#include "DoubleFieldSpinBox.h"
#include "ui_DoubleFieldSpinBox.h"

DoubleFieldSpinBox::DoubleFieldSpinBox(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DoubleFieldSpinBox)
{
	ui->setupUi(this);

	connect(ui->spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &DoubleFieldSpinBox::valueChanged);
}

DoubleFieldSpinBox::~DoubleFieldSpinBox()
{
	delete ui;
}

void DoubleFieldSpinBox::SetName(const QString & str)
{
	ui->label->setText(str);
}

void DoubleFieldSpinBox::SetValue(double value)
{
	ui->spinBox->setValue(value);
}

double DoubleFieldSpinBox::GetValue() const
{
	return ui->spinBox->value();
}

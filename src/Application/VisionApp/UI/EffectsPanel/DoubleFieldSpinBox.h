#pragma once

#include <QWidget>

namespace Ui {
class DoubleFieldSpinBox;
}

class DoubleFieldSpinBox : public QWidget
{
	Q_OBJECT

public:
	explicit DoubleFieldSpinBox(QWidget *parent = 0);
	~DoubleFieldSpinBox();

	void SetName(const QString &);
	void SetValue(double);
	double GetValue() const;

signals:
	void valueChanged(double);

private:
	Ui::DoubleFieldSpinBox *ui;
};

#pragma once

#include <QWidget>

namespace Ui {
class IntFieldSpinBox;
}

class IntFieldSpinBox : public QWidget
{
	Q_OBJECT

public:
	explicit IntFieldSpinBox(QWidget *parent = 0);
	~IntFieldSpinBox();

	void SetName(const QString &);
	void SetValue(int);
	double GetValue() const;

signals:
	void valueChanged(int);

private:
	Ui::IntFieldSpinBox *ui;
};

#pragma once

#include <QWidget>

namespace Ui {
class TopPanel;
}

class TopPanel : public QWidget
{
	Q_OBJECT

public:
	explicit TopPanel(QWidget *parent = 0);
	~TopPanel();

private:
	Ui::TopPanel *ui;
};

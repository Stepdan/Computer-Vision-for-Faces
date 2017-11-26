#pragma once

#include <QWidget>

namespace Ui {
class BottomPanel;
}

class BottomPanel : public QWidget
{
	Q_OBJECT

public:
	explicit BottomPanel(QWidget *parent = 0);
	~BottomPanel();

private:
	Ui::BottomPanel *ui;
};

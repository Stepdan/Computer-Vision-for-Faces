#pragma once

#include <QWidget>

namespace Ui {
class CapturePanel;
}

class CapturePanel : public QWidget
{
	Q_OBJECT

public:
	explicit CapturePanel(QWidget *parent = 0);
	~CapturePanel();

private:
	Ui::CapturePanel *ui;
};

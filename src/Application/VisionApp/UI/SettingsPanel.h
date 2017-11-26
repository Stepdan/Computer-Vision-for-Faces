#pragma once

#include <QWidget>

namespace Ui {
class SettingsPanel;
}

class SettingsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsPanel(QWidget *parent = 0);
	~SettingsPanel();

signals:
	void click();

private:
	Ui::SettingsPanel *ui;
};

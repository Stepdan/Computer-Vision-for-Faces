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

	void SetUndoEnabled(bool);
	void SetRedoEnabled(bool);

private:
	Ui::TopPanel *ui;
};

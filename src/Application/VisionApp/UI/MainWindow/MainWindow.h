#pragma once

#include <QMainWindow>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	void SetImage(const QImage & image);
	QImage GetImage() const;

	void UpdateStateUndoButtons(bool undoEnabled, bool redoEnabled);
	void UpdateImageInfoText(const QString & text);

signals:
	void applyEffect();

private:
	Ui::MainWindow *ui;
};

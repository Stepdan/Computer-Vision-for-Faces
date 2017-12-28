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

	void UpdateStateUndoButtons(bool undoEnabled, bool redoEnabled);
	void UpdateImageInfoText(const QString & text);

private slots:
	void OnUpdateInfoText(const QString &);

private:
	Ui::MainWindow *ui;

	QString m_imageInfo;
};

#pragma once

#include <QWidget>

namespace Ui {
class TrainingPanel;
}

class TrainingPanel : public QWidget
{
	Q_OBJECT

public:
	explicit TrainingPanel(QWidget *parent = 0);
	~TrainingPanel();

signals:
	void faceDetectClicked();

private slots:
	void OnFaceDetectClicked();
	void OnFolderClicked();
	void OnSaveLandmarksClicked();

private:
	Ui::TrainingPanel *ui;
};

#pragma once

#include <QWidget>

#include "Types/Face.h"

namespace Ui {
class TrainingPanel;
}

class TrainingPanel : public QWidget
{
	Q_OBJECT

public:
	explicit TrainingPanel(QWidget *parent = 0);
	~TrainingPanel();

private slots:
	void OnFaceDetectClicked();
	void OnFolderClicked();
	void OnSaveLandmarksClicked();

private:
	Ui::TrainingPanel *ui;

	Types::Face m_face;
};

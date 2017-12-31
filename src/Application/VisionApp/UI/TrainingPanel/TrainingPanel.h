#pragma once

#include <QWidget>

#include "Types/Pointers.h"
#include "TrainingTypes.h"

using namespace VisionApp::Training;

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
	void OnSettingsClicked();
	void OnSaveLandmarksClicked();

private:
	Ui::TrainingPanel *ui;

	SharedPtr<LandmarkFileSettings> m_landmarkFileSettings;
};

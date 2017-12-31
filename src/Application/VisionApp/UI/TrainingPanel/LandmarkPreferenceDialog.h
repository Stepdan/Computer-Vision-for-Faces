#pragma once

#include <QDialog>
#include <QSettings>

#include "Types/Pointers.h"
#include "Helpers/TrainingTypes.h"

using namespace VisionApp::Training;

namespace Ui {
class LandmarkPreferenceDialog;
}

class LandmarkPreferenceDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LandmarkPreferenceDialog(const SharedPtr<LandmarkFileSettings> & landmarkFileSettings, QWidget *parent = 0);
	~LandmarkPreferenceDialog();

private slots:
	void OnFolderBrowseClicked();
	void OnXMLBrowseClicked();
	void OnImagesPathClicked();

	void OnFolderPathChanged();
	void OnXMLPathChanged();
	void OnImagesPathChanged();

private:
	Ui::LandmarkPreferenceDialog *ui;

	SharedPtr<LandmarkFileSettings> m_landmarkFileSettings;
};

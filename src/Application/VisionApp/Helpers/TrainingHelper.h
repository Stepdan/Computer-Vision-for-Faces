#pragma once

#include <QObject>

#include "Types/Face.h"

#include "Proc/Settings/SettingsFaceDetection.h"

#include "ImageHelper.h"
#include "EffectHelper.h"
#include "TrainingTypes.h"

using namespace Core::Interfaces;
using namespace Proc::Interfaces;
using namespace VisionApp::Training;

namespace VisionApp {

class TrainingHelper : public QObject
{
	Q_OBJECT

public:
	TrainingHelper() = default;
	TrainingHelper(const SharedPtr<ImageHelper>&, const SharedPtr<EffectHelper>&);
	~TrainingHelper() = default;

	void SetFace(const SharedPtr<Types::Face> & face) { m_face = face; }
	SharedPtr<Types::Face> GetFace() const { return m_face; }

signals:
	void enableTrainingMode(bool enabled);
	void trainingFaceChanged(const SharedPtr<Types::Face> &);

	void needResetImage();
	void saveImage(const std::string &, const std::string &, Core::FlipOrientation);

private slots:
	void OnFaceDetectionClicked();
	void OnSaveLandmarksClicked();
	void OnCancelClicked();

	void OnLandmarkPosChanged();
	void OnLandmarkFileSettingsChanged(const SharedPtr<LandmarkFileSettings> &);

private:
	SharedPtr<ImageHelper> m_imageHelper;
	SharedPtr<EffectHelper> m_effectHelper;

	SharedPtr<Proc::SettingsFaceDetection> m_settings;
	SharedPtr<Types::Face> m_face;
	SharedPtr<LandmarkFileSettings> m_landmarkFileSettings;
};

}

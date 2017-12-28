#pragma once

#include <QObject>

#include "Types/Face.h"

#include "Proc/Settings/SettingsFaceDetection.h"

#include "EffectHelper.h"

using namespace Core::Interfaces;
using namespace Proc::Interfaces;

namespace VisionApp {

class TrainingHelper : public QObject
{
	Q_OBJECT

public:
	TrainingHelper() = default;
	TrainingHelper(const SharedPtr<EffectHelper>&);
	~TrainingHelper() = default;

	void SetFace(const SharedPtr<Types::Face> & face) { m_face = face; }
	SharedPtr<Types::Face> GetFace() const { return m_face; }

signals:
	void enableTrainingMode(bool enabled);
	void trainingFaceChanged(const SharedPtr<Types::Face> &);

	void needResetImage();

private slots:
	void OnFaceDetectionClicked();
	void OnSaveLandmarksClicked();
	void OnCancelClicked();

	void OnLandmarkPosChanged();

private:
	SharedPtr<EffectHelper> m_effectHelper;

	SharedPtr<Proc::SettingsFaceDetection> m_settings;
	SharedPtr<Types::Face> m_face;
};

}

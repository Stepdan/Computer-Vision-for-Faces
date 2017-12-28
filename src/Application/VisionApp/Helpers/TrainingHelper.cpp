#include "TrainingHelper.h"

#include <cassert>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "Proc/Settings/SettingsDrawLandmarks.h"

namespace VisionApp {

TrainingHelper::TrainingHelper(const SharedPtr<EffectHelper>& helper)
	: m_effectHelper(helper)
{
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::RESET, this, SIGNAL(needResetImage()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::ENABLE_TRAINING_MODE, this, SIGNAL(enableTrainingMode(bool)));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_FACE_CHANGED, this, SIGNAL(trainingFaceChanged(const SharedPtr<Types::Face> &)));

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_FACE_DETECT_CLICKED   , this, SLOT(OnFaceDetectionClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_SAVE_LANDMARKS_CLICKED, this, SLOT(OnSaveLandmarksClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_CANCEL_CLICKED        , this, SLOT(OnCancelClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_LANDMARK_CHANGED      , this, SLOT(OnLandmarkPosChanged()));
}

void TrainingHelper::OnFaceDetectionClicked()
{
	m_settings.reset(new Proc::SettingsFaceDetection());
	m_effectHelper->ApplyEffect(m_settings);

	assert(m_settings->GetFacesCount() == 1);
	if(m_settings->GetFacesCount() != 1)
		return;

	m_face.reset(new Face(m_settings->GetFace(0)));

	emit enableTrainingMode(true); // посылаем сигнал о том, что сцена переходит в train режим
	emit trainingFaceChanged(m_face);
}

void TrainingHelper::OnSaveLandmarksClicked()
{
	emit enableTrainingMode(false); // отключаем train режим сцены

	// @todo save face
}

void TrainingHelper::OnCancelClicked()
{
	emit enableTrainingMode(false); // отключаем train режим сцены
}

void TrainingHelper::OnLandmarkPosChanged()
{
	emit needResetImage();

	SharedPtr<Proc::SettingsDrawLandmarks> settings(new Proc::SettingsDrawLandmarks());
	settings->SetFace(*m_face);
	m_effectHelper->ApplyEffect(settings);
}

}

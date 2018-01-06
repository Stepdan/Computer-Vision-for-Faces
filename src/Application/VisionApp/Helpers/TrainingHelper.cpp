#include "TrainingHelper.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "Proc/Settings/SettingsDrawLandmarks.h"

namespace {

std::string LandmarkIndexToString(size_t index)
{
	if(index < 10)
		return "0"+std::to_string(index);

	return std::to_string(index);
}

}

namespace VisionApp {

TrainingHelper::TrainingHelper(const SharedPtr<ImageHelper>& imageHelper, const SharedPtr<EffectHelper>& effectsHelper)
	: m_imageHelper(imageHelper)
	, m_effectHelper(effectsHelper)
{
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::RESET, this, SIGNAL(needResetImage()));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::ENABLE_TRAINING_MODE, this, SIGNAL(enableTrainingMode(bool)));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_FACE_CHANGED, this, SIGNAL(trainingFaceChanged(const SharedPtr<Types::Face> &)));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::SAVE_IMAGE_CUSTOM, this, SIGNAL(saveImage(const std::string &, const std::string &, Core::FlipOrientation)));

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_FACE_DETECT_CLICKED   , this, SLOT(OnFaceDetectionClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_SAVE_LANDMARKS_CLICKED, this, SLOT(OnSaveLandmarksClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_CANCEL_CLICKED        , this, SLOT(OnCancelClicked()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_LANDMARK_CHANGED      , this, SLOT(OnLandmarkPosChanged()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_LANDMARK_FILE_SETTINGS_CHANGED , this, SLOT(OnLandmarkFileSettingsChanged(const SharedPtr<LandmarkFileSettings> &)));
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
	const auto frameInfo = m_imageHelper->GetDataImage()->GetFrameInfo();

	emit enableTrainingMode(false); // отключаем train режим сцены
	emit needResetImage(); // делаем reset, чтобы убрать landmark-и

/*
Данные, которые необходимо сохранить:
1. Кадр + зеркальная копия.
2. Дописываем полный путь к картинке в отдельный файл, хранящий эти пути.
3. Записываем координаты в отдельный файл + координаты прямоугольника, в который вписано лицо.
4. Дописываем в специальный xml-файл информацию о координатах.
*/

// 1. Кадр + зеркальная копия.
	const auto filename = (m_landmarkFileSettings->m_folderPath + "/" + QString::fromStdString(m_imageHelper->GetFilename())).toStdString();
	const auto filenameMirror = filename + "_mirror";
	emit saveImage(filename, "jpg", Core::FlipOrientation::Default);
	emit saveImage(filenameMirror, "jpg", Core::FlipOrientation::Horizontal);

// 2. Дописываем полный путь к картинке в отдельный файл, хранящий эти пути.
	std::ofstream imagesPathStream;
	imagesPathStream.open(m_landmarkFileSettings->m_imagesPath.toStdString(), std::ios::app);
	imagesPathStream << filename + ".jpg" << std::endl;
	imagesPathStream << filenameMirror + ".jpg" << std::endl;
	imagesPathStream.close();

// 3. Записываем координаты в отдельный файл + координаты прямоугольника, в который вписано лицо.
	//@todo Сейчас нельзя редактировать точки прямоугольника
	// Landmarks
	std::ofstream coordsStream;
	coordsStream.open(filename + "_bv70.txt");
	coordsStream << *m_face;
	coordsStream.close();

	coordsStream.open(filenameMirror + "_bv70.txt");
	coordsStream << m_face->GetInvertedPoints(frameInfo.width);
	coordsStream.close();

	// Face rect
	std::ofstream rectStream;
	rectStream.open(filename + "_rect.txt");
	const auto faceRect = m_face->GetFrame();
	rectStream << faceRect.first.x << " " <<
				  faceRect.first.y << " " <<
				  faceRect.second.x - faceRect.first.x << " " <<
				  faceRect.second.y - faceRect.first.y << std::endl;
	rectStream.close();

	rectStream.open(filenameMirror + "_rect.txt");
	const auto invertedFaceRect = m_face->GetInvertedFrame(frameInfo.width);
	rectStream << invertedFaceRect.first.x << " " <<
				  invertedFaceRect.first.y << " " <<
				  invertedFaceRect.second.x - invertedFaceRect.first.x << " " <<
				  invertedFaceRect.second.y - invertedFaceRect.first.y << std::endl;
	rectStream.close();

// 4. Дописываем в специальный xml-файл информацию о координатах
	std::ofstream xmlStream;
//-------------------------------------------------------------------------------------------------------------
	xmlStream.open(m_landmarkFileSettings->m_xmlPath.toStdString(), std::ios::app);
	xmlStream << "<image file=\"" << filename + ".jpg" << "\">" << std::endl;
	xmlStream << "\t<box height=\"" << faceRect.second.y - faceRect.first.y <<"\" "
			  << "left=\""  << faceRect.first.x << "\" "
			  << "top=\""   << faceRect.first.y << "\" "
			  << "width=\"" << faceRect.second.x - faceRect.first.x << "\">" << std::endl;
	const auto faceContour = m_face->GetAllPoints();
	for(size_t i = 0; i < faceContour.size(); ++i)
		xmlStream << "\t\t<part name=\"" << LandmarkIndexToString(i) << "\" "
				  << "x=\"" << std::to_string(faceContour[i].x) << "\" "
				  << "y=\"" << std::to_string(faceContour[i].y) << "\"/>" << std::endl;
	xmlStream << "\t</box>" << std::endl;
	xmlStream << "</image>" << std::endl;
//-------------------------------------------------------------------------------------------------------------
	xmlStream << "<image file=\"" << filenameMirror + ".jpg" << "\">" << std::endl;
	xmlStream << "\t<box height=\"" << invertedFaceRect.second.y - invertedFaceRect.first.y <<"\" "
			  << "left=\""  << invertedFaceRect.first.x << "\" "
			  << "top=\""   << invertedFaceRect.first.y << "\" "
			  << "width=\"" << invertedFaceRect.second.x - invertedFaceRect.first.x << "\">" << std::endl;
	const auto invertedFaceContour = m_face->GetInvertedPoints(frameInfo.width);
	for(size_t i = 0; i < invertedFaceContour.size(); ++i)
		xmlStream << "\t\t<part name=\"" << LandmarkIndexToString(i) << "\" "
				  << "x=\"" << std::to_string(invertedFaceContour[i].x) << "\" "
				  << "y=\"" << std::to_string(invertedFaceContour[i].y) << "\"/>" << std::endl;
	xmlStream << "\t</box>" << std::endl;
	xmlStream << "</image>" << std::endl;
	xmlStream.close();
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

void TrainingHelper::OnLandmarkFileSettingsChanged(const SharedPtr<LandmarkFileSettings> & landmarkFileSettings)
{
	m_landmarkFileSettings = landmarkFileSettings;
}

}

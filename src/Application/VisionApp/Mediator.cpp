#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QFileInfo>
#include <QFileDialog>
#include <QString>

#include "Core/DataImage/CvDataImage.h"
#include "Core/DataImage/QDataImage.h"

#include "Capture/Controller/CaptureController.h"

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "Application.h"
#include "Mediator.h"

namespace
{
const QString COMPANY_NAME = "StepCo";
const QString PRODUCT_NAME = "VisionApp";

const QString LAST_OPEN_PATH = "LAST_OPEN_PATH";
const QString LAST_SAVE_PATH = "LAST_SAVE_PATH";
}

namespace VisionApp {

Mediator::Mediator(const SharedPtr<MainWindow> & mainWindow)
	: m_mainWindow(mainWindow)
	, m_settings(new QSettings(COMPANY_NAME, PRODUCT_NAME))
	, m_imageHelper(new ImageHelper())
	, m_effectHelper(new EffectHelper(m_imageHelper))
	, m_undoHelper(new UndoHelper())
	, m_capture(new Capture::CaptureController())
{
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::LOAD_IMAGE, this, SLOT(OnLoadImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::LOAD_IMAGE2, this, SLOT(OnLoadImage2()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::SAVE_IMAGE, this, SLOT(OnSaveImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::UNDO, this, SLOT(OnUndo()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::REDO, this, SLOT(OnRedo()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::RESET, this, SLOT(OnReset()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::COMPARE_PRESSED, this, SLOT(OnCompare()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::COMPARE_RELEASED, this, SLOT(OnCompare()));

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::EFFECT_APPLYED, this, SLOT(OnApplyEffect(const SharedPtr<Proc::BaseSettings>&)));

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::CAPTURE_STARTED, this, SLOT(OnStartCapture()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::CAPTURE_CANCELED, this, SLOT(OnStopCapture()));

	qRegisterMetaType<Capture::CaptureInfo>("Capture::CaptureInfo");
	connect(m_capture.get(), &Capture::CaptureController::frameCaptured, this, &Mediator::OnFrameCaptured);
	connect(m_capture.get(), &Capture::CaptureController::captureInfoChanged, this, &Mediator::OnCaptureInfoChanged);
}

void Mediator::OnLoadImage()
{
	if(m_capture->IsCaptured())
		m_capture->Stop();

	OnReset();

	const auto lastPath = m_settings->value(LAST_OPEN_PATH, "C:/").toString();

	const QString filter = "All Files (*.*)";
	const auto filename = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", lastPath, filter);

	if(filename.isEmpty())
		return;

	m_imageHelper->SetImage(cv::imread(filename.toStdString()));
	const auto image = m_imageHelper->GetQImage();

	m_undoHelper->SetOriginal(m_imageHelper->GetDataImage());
	m_mainWindow->SetImage(image);

	m_settings->setValue(LAST_OPEN_PATH, filename);

	m_mainWindow->UpdateImageInfoText(
				QFileInfo(filename).baseName() + "." + QFileInfo(filename).suffix()
				+ " - width: "  + QString::number(image.width())
				+ ", height: " + QString::number(image.height()) );
}

void Mediator::OnLoadImage2()
{
	const auto lastPath = m_settings->value(LAST_OPEN_PATH, "C:/").toString();

	const QString filter = "All Files (*.*)";
	const auto filename = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", lastPath, filter);

	if(filename.isEmpty())
		return;

	m_imageHelper->SetImage2(cv::imread(filename.toStdString()));
}

void Mediator::OnSaveImage()
{
	const auto lastPath = m_settings->value(LAST_SAVE_PATH, "C:/").toString();

	const QString filter = "Images (*.png, *.bmp, *.jpg)";
	const auto filename = QFileDialog::getSaveFileName(m_mainWindow.get(), "Save file", lastPath, filter);

	if(filename.isEmpty())
		return;

	cv::imwrite(filename.toStdString(), m_imageHelper->GetCvMat());

	m_settings->setValue(LAST_SAVE_PATH, filename);
}

void Mediator::OnUndo()
{
	m_imageHelper->SetImage(m_undoHelper->Undo());
	m_mainWindow->SetImage(m_imageHelper->GetQImage());
	m_mainWindow->UpdateStateUndoButtons(m_undoHelper->UndoSize(), m_undoHelper->RedoSize());
}

void Mediator::OnRedo()
{
	m_imageHelper->SetImage(m_undoHelper->Redo());
	m_mainWindow->SetImage(m_imageHelper->GetQImage());
	m_mainWindow->UpdateStateUndoButtons(m_undoHelper->UndoSize(), m_undoHelper->RedoSize());
}

void Mediator::OnReset()
{
	m_imageHelper->SetImage(m_undoHelper->Reset());
	m_mainWindow->SetImage(m_imageHelper->GetQImage());
	m_mainWindow->UpdateStateUndoButtons(false, false);

	m_capture->ClearEffects();
}

void Mediator::OnCompare()
{
	const auto image = m_imageHelper->GetDataImage();
	m_imageHelper->SetImage(m_undoHelper->GetOriginal());
	m_mainWindow->SetImage(m_imageHelper->GetQImage());
	m_undoHelper->SetOriginal(image);
}

void Mediator::OnApplyEffect(const SharedPtr<Proc::BaseSettings>& settings)
{
	m_effectHelper->ApplyEffect(settings);
	m_capture->AddEffect(*settings);

	m_undoHelper->Add(m_imageHelper->GetDataImage());
	m_mainWindow->SetImage(m_imageHelper->GetQImage());
	m_mainWindow->UpdateStateUndoButtons(m_undoHelper->UndoSize(), m_undoHelper->RedoSize());
}

void Mediator::OnStartCapture()
{
	m_capture->Start();
}

void Mediator::OnStopCapture()
{
	m_capture->Stop();
}

void Mediator::OnFrameCaptured(const QImage & frame)
{
	m_mainWindow->SetImage(frame);
}

void Mediator::OnCaptureInfoChanged(const Capture::CaptureInfo & info)
{
	m_mainWindow->UpdateImageInfoText(
				"Width: "  + QString::number(info.width)  + " "
				"Height: " + QString::number(info.height) + " "
				"FPS: "    + QString::number(info.fps));
}

}

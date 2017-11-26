#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QFileDialog>
#include <QString>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "ImageUtils/ImageUtils.h"

#include "Mediator.h"

#include "Proc/Settings/SettingsDetailsEnhance.h"

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
	, m_effectHelper(new EffectHelper())
	, m_undoHelper(new UndoHelper())
{
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::LOAD_IMAGE, this, SLOT(OnLoadImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::SAVE_IMAGE, this, SLOT(OnSaveImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::UNDO, this, SLOT(OnUndo()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::REDO, this, SLOT(OnRedo()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::RESET, this, SLOT(OnReset()));

	connect(m_mainWindow.get(), &MainWindow::applyEffect, this, &Mediator::OnApplyEffect);
}

void Mediator::OnLoadImage()
{
	OnReset();

	const auto lastPath = m_settings->value(LAST_OPEN_PATH, "C:/").toString();

	const QString filter = "All Files (*.*)";
	const auto filename = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", lastPath, filter);

	if(filename.isEmpty())
		return;

	const auto image = Utils::Image::cvMat2QImage(cv::imread(filename.toStdString()));
	m_undoHelper->SetOriginal(image);
	m_mainWindow->SetImage(image);

	m_settings->setValue(LAST_OPEN_PATH, filename);
}

void Mediator::OnSaveImage()
{
	const auto lastPath = m_settings->value(LAST_SAVE_PATH, "C:/").toString();

	const QString filter = "Images (*.png, *.bmp, *.jpg)";
	const auto filename = QFileDialog::getSaveFileName(m_mainWindow.get(), "Save file", lastPath, filter);

	if(filename.isEmpty())
		return;

	cv::imwrite(filename.toStdString(), Utils::Image::QPixmap2cvMat(m_mainWindow->GetImage()));

	m_settings->setValue(LAST_SAVE_PATH, filename);
}

void Mediator::OnUndo()
{
	m_mainWindow->SetImage(m_undoHelper->Undo());
}

void Mediator::OnRedo()
{
	m_mainWindow->SetImage(m_undoHelper->Redo());
}

void Mediator::OnReset()
{
	m_mainWindow->SetImage(m_undoHelper->Reset());
}

void Mediator::OnApplyEffect()
{
	const auto effect = m_effectHelper->CreateEffectOne(Proc::SettingsDetailsEnhance());
	cv::Mat dst;
	effect->Apply(Utils::Image::QPixmap2cvMat(m_mainWindow->GetImage()), dst);
	const auto image = Utils::Image::cvMat2QImage(dst);
	m_undoHelper->Add(image);
	m_mainWindow->SetImage(image);
}

}

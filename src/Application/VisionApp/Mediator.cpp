#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QFileDialog>
#include <QString>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "ImageUtils/ImageUtils.h"

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
{
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::LOAD_IMAGE, this, SLOT(OnLoadImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::SAVE_IMAGE, this, SLOT(OnSaveImage()));
}

void Mediator::OnLoadImage()
{
	const auto lastPath = m_settings->value(LAST_OPEN_PATH, "C:/").toString();

	const QString filter = "All Files (*.*)";
	const auto filename = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", lastPath, filter);

	if(filename.isEmpty())
		return;

	auto cvMat = cv::imread(filename.toStdString());
	m_mainWindow->SetImage(Utils::Image::cvMat2QImage(cvMat));

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

}

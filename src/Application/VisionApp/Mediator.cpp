#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QFileDialog>
#include <QString>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

#include "ImageUtils/ImageUtils.h"

#include "Mediator.h"

namespace VisionApp {

Mediator::Mediator(const SharedPtr<MainWindow> & mainWindow)
	: m_mainWindow(mainWindow)
{
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::LOAD_IMAGE, this, SLOT(OnLoadImage()));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::SAVE_IMAGE, this, SLOT(OnSaveImage()));
}

void Mediator::OnLoadImage()
{
	const QString filter = "All Files (*.*)";
	const auto filename = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", "C:/", filter);
	auto cvMat = cv::imread(filename.toStdString());
	m_mainWindow->SetImage(Utils::Image::cvMat2QImage(cvMat));
}

void Mediator::OnSaveImage()
{
	const QString filter = "Images (*.png, *.bmp, *.jpg)";
	const auto filename = QFileDialog::getSaveFileName(m_mainWindow.get(), "Save file", "C:/", filter);
	cv::imwrite(filename.toStdString(), Utils::Image::QPixmap2cvMat(m_mainWindow->GetImage()));
}

}

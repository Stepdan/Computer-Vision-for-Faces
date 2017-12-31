#pragma once

#include <QObject>

#include "Core/DataImage/CvDataImage.h"
#include "Core/DataImage/QDataImage.h"

using namespace Core::Interfaces;

namespace VisionApp {

class ImageHelper : public QObject
{
	Q_OBJECT

public:
	ImageHelper();
    ~ImageHelper() = default;

public:
	void SetImage(const SharedPtr<IDataImage>&, bool needToUpdate = false);
	void SetImage(const Core::QDataImage&, bool needToUpdate = false);
	void SetImage(const Core::CvDataImage&, bool needToUpdate = false);
	void SetImage(const QImage&, bool needToUpdate = false);
	void SetImage(const cv::Mat&, bool needToUpdate = false);

	void SetFilename(const std::string &);
	std::string GetFilename() const;

    SharedPtr<IDataImage> GetDataImage();
    QImage GetQImage();
    cv::Mat GetCvMat();

	void SetImage2(const cv::Mat&);
	cv::Mat GetCvMat2();

	QImage Convert2QImage(const SharedPtr<IDataImage> &);
	QImage Convert2QImage(const cv::Mat &);
	cv::Mat Convert2cvImage(const SharedPtr<IDataImage> &);

signals:
	void imageChanged();

private slots:
	void OnSaveImage(const std::string & filepath, const std::string & extension, Core::FlipOrientation);

private:
	SharedPtr<IDataImage> m_image; // Основное изображение
	SharedPtr<IDataImage> m_image2; // Изображение, используемое как дополнительное для эффектов

	std::string m_filename;
};

}

#pragma once

#include "Core/DataImage/CvDataImage.h"
#include "Core/DataImage/QDataImage.h"

using namespace Core::Interfaces;

namespace VisionApp {

class ImageHelper
{
public:
    ImageHelper() = default;
    ~ImageHelper() = default;

public:
    void SetImage(const SharedPtr<IDataImage>&);
    void SetImage(const Core::QDataImage&);
    void SetImage(const Core::CvDataImage&);
    void SetImage(const QImage&);
    void SetImage(const cv::Mat&);

    SharedPtr<IDataImage> GetDataImage();
    QImage GetQImage();
    cv::Mat GetCvMat();

	void SetImage2(const cv::Mat&);
	cv::Mat GetCvMat2();

	QImage Convert2QImage(const SharedPtr<IDataImage> &);
	QImage Convert2QImage(const cv::Mat &);
	cv::Mat Convert2cvImage(const SharedPtr<IDataImage> &);

private:
	SharedPtr<IDataImage> m_image; // Основное изображение
	SharedPtr<IDataImage> m_image2; // Изображение, используемое как дополнительное для эффектов
};

}

#include "ImageHelper.h"

#include "Core/Utils/ImageUtils.h"

namespace VisionApp {

void ImageHelper::SetImage(const SharedPtr<IDataImage>& dataImage)
{
    m_image = dataImage;
}

void ImageHelper::SetImage(const Core::QDataImage& qDataImage)
{
    m_image.reset(new Core::QDataImage(qDataImage));
}

void ImageHelper::SetImage(const Core::CvDataImage& cvDataImage)
{
    m_image.reset(new Core::CvDataImage(cvDataImage));
}

void ImageHelper::SetImage(const QImage& qImage)
{
    m_image.reset(new Core::QDataImage(qImage));
}

void ImageHelper::SetImage(const cv::Mat& cvMat)
{
    m_image.reset(new Core::CvDataImage(cvMat));
}


SharedPtr<IDataImage> ImageHelper::GetDataImage()
{
    return m_image;
}

QImage ImageHelper::GetQImage()
{
	if(!m_image)
		return QImage();

    switch(m_image->GetImpl())
    {
    case Core::ImageImpl::Qt:
        return dynamic_cast<Core::QDataImage*>(m_image.get())->GetQImage();
    case Core::ImageImpl::OpenCV:
        return Core::Utils::cvMat2QImage(dynamic_cast<Core::CvDataImage*>(m_image.get())->GetCvMat());
    }
}

cv::Mat ImageHelper::GetCvMat()
{
    switch(m_image->GetImpl())
    {
    case Core::ImageImpl::Qt:
        return Core::Utils::QImage2cvMat(dynamic_cast<Core::QDataImage*>(m_image.get())->GetQImage());
    case Core::ImageImpl::OpenCV:
        return dynamic_cast<Core::CvDataImage*>(m_image.get())->GetCvMat();
    }
}


}

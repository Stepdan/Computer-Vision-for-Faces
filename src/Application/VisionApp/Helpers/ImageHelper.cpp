#include "ImageHelper.h"

#include "Core/Utils/ImageUtils.h"

namespace VisionApp {

void ImageHelper::SetImage(const SharedPtr<IDataImage>& dataImage, bool needToUpdate)
{
    m_image = dataImage;
	if(needToUpdate)
		emit imageChanged();
}

void ImageHelper::SetImage(const Core::QDataImage& qDataImage, bool needToUpdate)
{
    m_image.reset(new Core::QDataImage(qDataImage));
	if(needToUpdate)
		emit imageChanged();
}

void ImageHelper::SetImage(const Core::CvDataImage& cvDataImage, bool needToUpdate)
{
    m_image.reset(new Core::CvDataImage(cvDataImage));
	if(needToUpdate)
		emit imageChanged();
}

void ImageHelper::SetImage(const QImage& qImage, bool needToUpdate)
{
    m_image.reset(new Core::QDataImage(qImage));
	if(needToUpdate)
		emit imageChanged();
}

void ImageHelper::SetImage(const cv::Mat& cvMat, bool needToUpdate)
{
    m_image.reset(new Core::CvDataImage(cvMat));
	if(needToUpdate)
		emit imageChanged();
}

void ImageHelper::SetImage2(const cv::Mat& cvMat)
{
	m_image2.reset(new Core::CvDataImage(cvMat));
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

cv::Mat ImageHelper::GetCvMat2()
{
	switch(m_image2->GetImpl())
	{
	case Core::ImageImpl::Qt:
		return Core::Utils::QImage2cvMat(dynamic_cast<Core::QDataImage*>(m_image2.get())->GetQImage());
	case Core::ImageImpl::OpenCV:
		return dynamic_cast<Core::CvDataImage*>(m_image2.get())->GetCvMat();
	}
}

QImage ImageHelper::Convert2QImage(const SharedPtr<IDataImage> & image)
{
	switch(image->GetImpl())
	{
	case Core::ImageImpl::Qt:
		return dynamic_cast<Core::QDataImage*>(image.get())->GetQImage();
	case Core::ImageImpl::OpenCV:
		return Core::Utils::cvMat2QImage(dynamic_cast<Core::CvDataImage*>(image.get())->GetCvMat());
	}
}

QImage ImageHelper::Convert2QImage(const cv::Mat & cvImage)
{
	return Core::Utils::cvMat2QImage(cvImage);
}

cv::Mat ImageHelper::Convert2cvImage(const SharedPtr<IDataImage> & image)
{
	switch(image->GetImpl())
	{
	case Core::ImageImpl::Qt:
		return Core::Utils::QImage2cvMat(dynamic_cast<Core::QDataImage*>(image.get())->GetQImage());
	case Core::ImageImpl::OpenCV:
		return dynamic_cast<Core::CvDataImage*>(image.get())->GetCvMat();
	}
}

}

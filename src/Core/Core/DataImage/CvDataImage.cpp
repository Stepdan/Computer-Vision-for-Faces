#include "CvDataImage.h"
#include "QDataImage.h"

#include "Core/Utils/ImageUtils.h"

namespace Core {

CvDataImage::CvDataImage(const cv::Mat& mat)
    : m_image(mat)
{

}

CvDataImage::CvDataImage(const CvDataImage& rhs)
{
    this->m_image = rhs.m_image;
}

CvDataImage& CvDataImage::operator=(const CvDataImage& rhs)
{
    this->m_image = rhs.m_image;
    return *this;
}

CvDataImage::~CvDataImage()
{
}

SharedPtr<IDataImage> CvDataImage::Clone()
{
    SharedPtr<IDataImage> imagePtr(new CvDataImage(*this));
    return imagePtr;
}

ImageImpl CvDataImage::GetImpl() const
{
    return ImageImpl::OpenCV;
}

SharedPtr<IDataImage> CvDataImage::ChangeImpl()
{
    SharedPtr<IDataImage> imageImpl(new QDataImage(Utils::cvMat2QImage(m_image)));
    return imageImpl;
}

void CvDataImage::ColorSpaceConvert(ColorSpace cs)
{

}

const FrameInfo & CvDataImage::GetFrameInfo()
{
    return { m_image.cols, m_image.rows };
}

}

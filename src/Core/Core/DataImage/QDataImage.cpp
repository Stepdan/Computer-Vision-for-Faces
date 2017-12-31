#include <cassert>

#include "QDataImage.h"
#include "CvDataImage.h"

#include "Core/Utils/ImageUtils.h"

namespace Core {

QDataImage::QDataImage(const QImage& mat)
    : m_image(mat)
{

}

QDataImage::QDataImage(const QDataImage& rhs)
{
    this->m_image = rhs.m_image;
}

QDataImage& QDataImage::operator=(const QDataImage& rhs)
{
    this->m_image = rhs.m_image;
    return *this;
}

QDataImage::~QDataImage()
{
}

SharedPtr<IDataImage> QDataImage::Clone()
{
    SharedPtr<IDataImage> imagePtr(new QDataImage(*this));
    return imagePtr;
}

ImageImpl QDataImage::GetImpl() const
{
    return ImageImpl::Qt;
}

SharedPtr<IDataImage> QDataImage::ChangeImpl()
{
    SharedPtr<IDataImage> imageImpl(new CvDataImage(Utils::QImage2cvMat(m_image)));
    return imageImpl;
}

void QDataImage::ColorSpaceConvert(ColorSpace cs)
{

}

FrameInfo QDataImage::GetFrameInfo()
{
    return { m_image.width(), m_image.height() };
}

SharedPtr<IDataImage> QDataImage::Subframe(int x0, int y0, int width, int height)
{
	return SharedPtr<IDataImage>(new QDataImage(m_image.copy(x0, y0, width, height)));
}

SharedPtr<IDataImage> QDataImage::Flip(FlipOrientation orientation)
{
	bool h = false, v = false;

	switch(orientation)
	{
	case FlipOrientation::Diagonal:
		h = v = true;
		break;
	case FlipOrientation::Horizontal:
		h = true;
		break;
	case FlipOrientation::Vertical:
		v = true;
		break;
	}

	return SharedPtr<IDataImage>(new QDataImage(m_image.mirrored(h, v)));
}

void QDataImage::Save(const std::string & pathname, const std::string & extension)
{
	std::string filename = pathname + "." + extension;
	m_image.save(QString::fromStdString(filename));
}

}

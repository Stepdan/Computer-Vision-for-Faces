#pragma once

#include <QImage>

#include "Core/Interfaces/IDataImage.h"

using namespace Core::Interfaces;

namespace Core {

class QDataImage : public IDataImage
{
public:
    QDataImage() = default;
    QDataImage(const QImage&);
    QDataImage(const QDataImage&);
    QDataImage& operator=(const QDataImage&);
    ~QDataImage();

public: // IDataImage
    SharedPtr<IDataImage> Clone()         override;
    ImageImpl             GetImpl() const override;
    SharedPtr<IDataImage> ChangeImpl()    override;
    void                  ColorSpaceConvert(ColorSpace cs) override;
	FrameInfo             GetFrameInfo()  override;
	SharedPtr<IDataImage> Subframe(int x0 = 0, int y0 = 0, int width = -1, int height = -1) override;
	SharedPtr<IDataImage> Flip(FlipOrientation) override;
	void                  Save(const std::string & pathname, const std::string & extension = "png") override;

public:
    QImage GetQImage() const { return m_image; }

private:
    QImage m_image;
};

}

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
    const FrameInfo &     GetFrameInfo()  override;

public:
    QImage GetQImage() const { return m_image; }

private:
    QImage m_image;
};

}

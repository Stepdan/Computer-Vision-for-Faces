#pragma once

#include "opencv2/imgproc/types_c.h"

#include "Core/Interfaces/IDataImage.h"

using namespace Core::Interfaces;

namespace Core {

class CvDataImage : public IDataImage
{
public:
    CvDataImage() = default;
    CvDataImage(const cv::Mat&);
    CvDataImage(const CvDataImage&);
    CvDataImage& operator=(const CvDataImage&);
    ~CvDataImage();

public: // IDataImage
    SharedPtr<IDataImage> Clone()         override;
    ImageImpl             GetImpl() const override;
    SharedPtr<IDataImage> ChangeImpl()    override;
    void                  ColorSpaceConvert(ColorSpace cs) override;
    const FrameInfo&      GetFrameInfo()  override;

public:
    cv::Mat GetCvMat() const { return m_image; }

private:
	cv::Mat m_image;
};

}

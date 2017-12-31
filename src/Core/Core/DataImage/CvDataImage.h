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
	FrameInfo             GetFrameInfo()  override;
	SharedPtr<IDataImage> Subframe(int x0 = 0, int y0 = 0, int width = -1, int height = -1) override;
	SharedPtr<IDataImage> Flip(FlipOrientation) override;
	void                  Save(const std::string & pathname, const std::string & extension = "png") override;

public:
    cv::Mat GetCvMat() const { return m_image; }

private:
	cv::Mat m_image;
};

}

#include "ImageUtils.h"

#include <cassert>

// cv::Mat должен быть RGB

namespace Utils { namespace Image {

QImage cvMat2QImage(const cv::Mat& mat)
{
	switch(mat.type())
	{
	case CV_8UC4:
		return QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
	case CV_8UC3:
		return QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
	case CV_8UC1:
		return QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
	default:
		assert(0 && "ImageUtils: Incorrect cv::Mat type!");
		return QImage();
		break;
	}
}

static inline QPixmap cvMat2QPixmap(const cv::Mat& mat)
{
	return QPixmap::fromImage(cvMat2QImage(mat));
}

cv::Mat QImage2cvMat(const QImage& image, bool cloneData/* = true*/)
{
	switch(image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_ARGB32_Premultiplied:
		{
			cv::Mat mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), static_cast<size_t>(image.bytesPerLine()));
			return (cloneData ? mat.clone() : mat);
		}
	case QImage::Format_RGB32:
	case QImage::Format_RGB888:
		{
			if(!cloneData)
			{
				assert(0 && "ImageUtils: Conversion requires cloning mode because temporary QImage is used!");
				return cv::Mat();
			}
			QImage swapped = image;
			if(image.format() == QImage::Format_RGB32)
				swapped.convertToFormat(QImage::Format_RGB888);
			swapped = swapped.rgbSwapped();

			return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), static_cast<size_t>(swapped.bytesPerLine())).clone();
		}
	case QImage::Format_Grayscale8:
		{
			cv::Mat mat(image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), static_cast<size_t>(image.bytesPerLine()));
			return (cloneData ? mat.clone() : mat);
		}
	}
}

cv::Mat QPixmap2cvMat(const QPixmap& pixmap, bool cloneData /*= true*/)
{
	return QImage2cvMat(pixmap.toImage(), cloneData);
}

}}

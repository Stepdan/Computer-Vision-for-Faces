#pragma once

#include <QImage>
#include <QPixmap>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

namespace Utils { namespace Image {

QImage cvMat2QImage(const cv::Mat& mat);

QPixmap cvMat2QPixmap(const cv::Mat& mat);

cv::Mat QImage2cvMat(const QImage& image, bool cloneData = true);

cv::Mat QPixmap2cvMat(const QPixmap& pixmap, bool cloneData = true);

}}

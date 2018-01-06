#pragma once

#include "opencv2/opencv.hpp"

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>

#include <vector>

#include "Types/Point.h"

namespace Proc { namespace Utils {

void Interpolation(unsigned char* lut, float* fullRange, float* Curve, float* originalValue);

void ApplyVignette(cv::Mat& image, float vignetteScale);

void AdjustContrast(cv::Mat& image, float alpha);

void ConstrainPoint(cv::Point2f & p, cv::Size sz);

void GetEightBoundaryPoints(cv::Size size, std::vector<cv::Point2f> & boundaryPts);

void DlibLandmarksToPoints(const std::vector<Types::Point> & landmarks, std::vector<cv::Point2f> & points);

void SimilarityTransform(std::vector<cv::Point2f>& inPoints, std::vector<cv::Point2f>& outPoints, cv::Mat &tform);

void NormalizeImagesAndLandmarks(cv::Size outSize, cv::Mat &imgIn, cv::Mat &imgOut, std::vector<cv::Point2f>& pointsIn, std::vector<cv::Point2f>& pointsOut);

int FindIndex(std::vector<cv::Point2f>& points, cv::Point2f &point);

void CalculateDelaunayTriangles(cv::Rect rect, std::vector<cv::Point2f> &points, std::vector< std::vector<int> > &delaunayTri);

void ApplyAffineTransform(cv::Mat &warpImage, cv::Mat &src, std::vector<cv::Point2f> &srcTri, std::vector<cv::Point2f> &dstTri);

void WarpTriangle(cv::Mat &img1, cv::Mat &img2, std::vector<cv::Point2f> t1, std::vector<cv::Point2f> t2);

bool RectAreaComparator(dlib::rectangle &r1, dlib::rectangle &r2);

void WarpImage(cv::Mat &imgIn, cv::Mat &imgOut, std::vector<cv::Point2f> &pointsIn, std::vector<cv::Point2f> &pointsOut, std::vector< std::vector<int> > &delaunayTri, bool useOutputImageSize = false);

void DrawDelaunayTriangles(cv::Mat &img, std::vector<cv::Point2f> &points, std::vector< std::vector<int> > &delaunayTri);

}}

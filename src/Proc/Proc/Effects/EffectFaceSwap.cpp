#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"

#include <ctime>

#include "Types/Face.h"

#include "EffectFaceSwap.h"
#include "Proc/Utils/ProcUtils.h"

#include "Proc/Effects/Factory/EffectsFactory.h"
#include "Proc/Settings/SettingsFaceDetection.h"

namespace Proc {

EffectFaceSwap::EffectFaceSwap(const SettingsFaceSwap & settings/* = SettingsFaceSwap()*/)
	: m_settings(settings)
{
	m_faceDetector = EffectsFactory::Instance().CreateEffectOne(SettingsFaceDetection::SETTINGS_ID);
}

void EffectFaceSwap::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsFaceSwap &>(settings);
}

const BaseSettings & EffectFaceSwap::GetBaseSettings() const
{
	return m_settings;
}

void EffectFaceSwap::Apply(const cv::Mat & src, cv::Mat & dst)
{
	auto image0 = src.clone();
	auto image1 = src.clone();
	dst = src.clone();

	// Ищем лица
	SettingsFaceDetection faceDetectionSettings;
	faceDetectionSettings.SetDrawWithLandmarks(false);
	m_faceDetector->SetBaseSettings(faceDetectionSettings);
	m_faceDetector->Apply(image0, image0);

	faceDetectionSettings = dynamic_cast<const SettingsFaceDetection&>(m_faceDetector->GetBaseSettings());
	if(faceDetectionSettings.GetFacesCount() < 2)
		return;

	srand(time(0));
	size_t i1;
	i1 = rand() % faceDetectionSettings.GetFacesCount();
	size_t i2 = faceDetectionSettings.GetFacesCount()+1;
	while(i2 == faceDetectionSettings.GetFacesCount()+1 || i2 == i1)
		i2 = rand() % faceDetectionSettings.GetFacesCount();
	m_settings.SetFaces( { faceDetectionSettings.GetFace(i1), faceDetectionSettings.GetFace(i2) } );

	auto faces = m_settings.GetFaces();

	auto firstFace  = faces.first.GetAllPoints();
	auto secondFace = faces.second.GetAllPoints();

	std::vector<cv::Point2f> points1, points2;
	Utils::DlibLandmarksToPoints(firstFace, points1);
	Utils::DlibLandmarksToPoints(secondFace, points2);

	// Выкидываем внутренние точки рта
	points1.erase(std::next(points1.begin(), 60), std::next(points1.begin(), 68));
	points2.erase(std::next(points2.begin(), 60), std::next(points2.begin(), 68));

	image0.convertTo(image0, CV_32F);
	image1.convertTo(image1, CV_32F);

	// Find convex hull
	std::vector<cv::Point2f> hull1, hull2;
	std::vector<cv::Point2f> hull1_t, hull2_t;
	std::vector<int> hullIndex;

	cv::convexHull(points2, hullIndex, false, false);
	for(int i = 0; i < hullIndex.size(); i++)
	{
		hull1_t.push_back(points1[hullIndex[i]]);
		hull2_t.push_back(points2[hullIndex[i]]);
	}

	for(int i = 0; i < points1.size(); i++)
	{
		hull1.push_back(points1[i]);
		hull2.push_back(points2[i]);
	}

	// Find delaunay triangulation for points on the convex hull
	std::vector< std::vector<int> > dt;
	cv::Rect rect(0, 0, image1.cols, image1.rows);
	Proc::Utils::CalculateDelaunayTriangles(rect, hull2, dt);

	// Apply affine transformation to Delaunay triangles
	for(size_t i = 0; i < dt.size(); i++)
	{
		std::vector<cv::Point2f> t1, t2;
		// Get points for img1, img2 corresponding to the triangles
		for(size_t j = 0; j < 3; j++)
		{
			t1.push_back(hull1[dt[i][j]]);
			t2.push_back(hull2[dt[i][j]]);
		}
		Proc::Utils::WarpTriangle(image0, image1, t1, t2);
		Proc::Utils::WarpTriangle(image0, image1, t2, t1);
	}

	// Calculate mask for seamless cloning
	std::vector<cv::Point> hull8U_1, hull8U_2;
	for(int i = 0; i < hull2_t.size(); i++)
	{
		cv::Point pt(hull2_t[i].x, hull2_t[i].y);
		hull8U_1.push_back(pt);

		cv::Point pt1(hull1_t[i].x, hull1_t[i].y);
		hull8U_2.push_back(pt1);
	}

	cv::Mat mask = cv::Mat::zeros(dst.rows, dst.cols, dst.depth());
	cv::fillConvexPoly(mask, &hull8U_1[0], hull8U_1.size(), cv::Scalar(255,255,255));

	cv::Mat mask1 = cv::Mat::zeros(dst.rows, dst.cols, dst.depth());
	cv::fillConvexPoly(mask1, &hull8U_2[0], hull8U_2.size(), cv::Scalar(255,255,255));

	// find center of the mask to be cloned with the destination image
	cv::Rect r = cv::boundingRect(hull2_t);
	cv::Point center = (r.tl() + r.br()) / 2;

	cv::Rect r1 = cv::boundingRect(hull1_t);
	cv::Point center1 = (r1.tl() + r1.br()) / 2;

	cv::Mat output;
	image1.convertTo(image1, dst.type());

	cv::imwrite("C:/Users/d.stepin/Desktop/Pictures/TEMP/image1.jpg", image1);
	cv::imwrite("C:/Users/d.stepin/Desktop/Pictures/TEMP/mask.jpg", mask);
	cv::imwrite("C:/Users/d.stepin/Desktop/Pictures/TEMP/mask1.jpg", mask1);

	cv::seamlessClone(image1, dst, mask, center, output, cv::NORMAL_CLONE);
	cv::seamlessClone(image1, output, mask1, center1, dst, cv::NORMAL_CLONE);

	auto delauneyImage = src.clone();
	Proc::Utils::DrawDelaunayTriangles(delauneyImage, hull1, dt);
	cv::imwrite("C:/Users/d.stepin/Desktop/Pictures/TEMP/delauneyImage.jpg", delauneyImage);
}

}

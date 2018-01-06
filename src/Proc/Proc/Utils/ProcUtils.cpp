#include "ProcUtils.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define M_PI       3.14159265358979323846   // pi

namespace Proc { namespace Utils {

void Interpolation(unsigned char* lut, float* fullRange, float* Curve, float* originalValue)
{
	int i;
	for (i=0; i < 256; ++i)
	{
		int j = 0;
		float a = fullRange[i];
		while(a > originalValue[j])
		{
			++j;
		}
		if (a == originalValue[j])
		{
			lut[i] = Curve[j];
			continue;
		}
		float slope = ((float)(Curve[j] - Curve[j-1]))/(originalValue[j] - originalValue[j-1]);
		float constant = Curve[j] - slope * originalValue[j];
		lut[i] = slope * fullRange[i] + constant;
	}
}

void ApplyVignette(cv::Mat& img, float vignetteScale)
{
	// convert to float
	// img = np.float32(img)
	int rows = img.rows;
	int cols = img.cols;

	// Compute the kernel size from the image dimensions
	int k = std::min(rows, cols) / vignetteScale;

	// Create a kernel to get the halo effect
	cv::Mat kernelX = cv::getGaussianKernel(cols,k);
	cv::Mat kernelY = cv::getGaussianKernel(rows,k);

	cv::Mat kernelX_Transpose;
	cv::transpose(kernelX, kernelX_Transpose);
	cv::Mat kernel = kernelY * kernelX_Transpose;

	// Normalize the kernel
	cv::Mat mask;
	cv::normalize(kernel, mask, 0, 1, cv::NORM_MINMAX);

	// Convert to float32
	img.convertTo(img,CV_32F);
	mask.convertTo(mask,CV_32F);

	// Split the channels
	std::vector<cv::Mat> channels(3);
	cv::split(img, channels);

	//Apply the halo all the channels of the image
	channels[0] += channels[0].mul(mask);
	channels[1] += channels[1].mul(mask);
	channels[2] += channels[2].mul(mask);

	// Merge the channels
	cv::merge(channels, img);
	img = img / 2;

	// Clipping operation performed to limit pixel values between 0 and 255
	cv::min(img, 255, img);
	cv::max(img, 0, img);

	// Convert back from float32
	img.convertTo(img, CV_8UC3);
}

void AdjustContrast(cv::Mat& img, float alpha)
{
	cv::Mat ycbImage;
	// Convert to YCrCb color space
	cv::cvtColor(img, ycbImage, cv::COLOR_BGR2YCrCb);
	// Convert to float32
	ycbImage.convertTo(ycbImage, CV_32F);
	std::vector<cv::Mat>channels(3);
	// Split the channels
	cv::split(ycbImage, channels);

	// Scale the Ychannel
	channels[0] = channels[0] * alpha;
	// Clipping operation performed to limit pixel values between 0 and 255
	cv::min(channels[0], 255, channels[0]);
	cv::max(channels[0], 0, channels[0]);

	// Merge the channels
	cv::merge(channels, ycbImage);

	// Convert back from float32
	ycbImage.convertTo(ycbImage, CV_8UC3);

	cv::Mat contrastImage;
	// Convert back to BGR
	cv::cvtColor(ycbImage, contrastImage, cv::COLOR_YCrCb2BGR);

	img = contrastImage;
}

void ConstrainPoint(cv::Point2f & p, cv::Size sz)
{
	p.x = std::min(std::max( (double)p.x, 0.0), (double)(sz.width - 1));
	p.y = std::min(std::max( (double)p.y, 0.0), (double)(sz.height - 1));
}

void GetEightBoundaryPoints(cv::Size size, std::vector<cv::Point2f> & boundaryPts)
{
	int h = size.height, w = size.width;
	boundaryPts.push_back(cv::Point2f(0,0));
	boundaryPts.push_back(cv::Point2f(w/2, 0));
	boundaryPts.push_back(cv::Point2f(w-1,0));
	boundaryPts.push_back(cv::Point2f(w-1, h/2));
	boundaryPts.push_back(cv::Point2f(w-1, h-1));
	boundaryPts.push_back(cv::Point2f(w/2, h-1));
	boundaryPts.push_back(cv::Point2f(0, h-1));
	boundaryPts.push_back(cv::Point2f(0, h/2));
}

void DlibLandmarksToPoints(const std::vector<Types::Point> & landmarks, std::vector<cv::Point2f> & points)
{
	// Loop over all landmark points
	for (int i = 0; i < landmarks.size(); i++)
	{
		cv::Point2f pt(landmarks[i].x, landmarks[i].y);
		points.push_back(pt);
	}
}

void SimilarityTransform(std::vector<cv::Point2f>& inPoints, std::vector<cv::Point2f>& outPoints, cv::Mat &tform)
{
	double s60 = sin(60 * M_PI / 180.0);
	double c60 = cos(60 * M_PI / 180.0);

	std::vector <cv::Point2f> inPts = inPoints;
	std::vector <cv::Point2f> outPts = outPoints;

	// Placeholder for the third point.
	inPts.push_back(cv::Point2f(0,0));
	outPts.push_back(cv::Point2f(0,0));

	// The third point is calculated so that the three points make an equilateral triangle
	inPts[2].x =  c60 * (inPts[0].x - inPts[1].x) - s60 * (inPts[0].y - inPts[1].y) + inPts[1].x;
	inPts[2].y =  s60 * (inPts[0].x - inPts[1].x) + c60 * (inPts[0].y - inPts[1].y) + inPts[1].y;

	outPts[2].x =  c60 * (outPts[0].x - outPts[1].x) - s60 * (outPts[0].y - outPts[1].y) + outPts[1].x;
	outPts[2].y =  s60 * (outPts[0].x - outPts[1].x) + c60 * (outPts[0].y - outPts[1].y) + outPts[1].y;

	// Now we can use estimateRigidTransform for calculating the similarity transform.
	tform = cv::estimateRigidTransform(inPts, outPts, false);
}

void NormalizeImagesAndLandmarks(cv::Size outSize, cv::Mat &imgIn, cv::Mat &imgOut, std::vector<cv::Point2f>& pointsIn, std::vector<cv::Point2f>& pointsOut)
{
	int h = outSize.height;
	int w = outSize.width;

	std::vector<cv::Point2f> eyecornerSrc;
	// Get the locations of the left corner of left eye
	eyecornerSrc.push_back(pointsIn[36]);
	// Get the locations of the right corner of right eye
	eyecornerSrc.push_back(pointsIn[45]);

	std::vector<cv::Point2f> eyecornerDst;
	// Location of the left corner of left eye in normalized image.
	eyecornerDst.push_back(cv::Point2f( 0.3*w, h/3));
	// Location of the right corner of right eye in normalized image.
	eyecornerDst.push_back(cv::Point2f( 0.7*w, h/3));

	// Calculate similarity transform
	cv::Mat tform;
	SimilarityTransform(eyecornerSrc, eyecornerDst, tform);

	// Apply similarity transform to input image
	imgOut = cv::Mat::zeros(h, w, CV_32FC3);
	cv::warpAffine(imgIn, imgOut, tform, imgOut.size());

	// Apply similarity transform to landmarks
	cv::transform( pointsIn, pointsOut, tform);
}

int FindIndex(std::vector<cv::Point2f>& points, cv::Point2f &point)
{
	int minIndex = 0;
	auto dp = points[0] - point;
	double minDistance = sqrt(dp.x * dp.x + dp.y * dp.y);
	for(int i = 1; i < points.size(); i++)
	{
		dp = points[i] - point;
		double distance = sqrt(dp.x * dp.x + dp.y * dp.y);
		if( distance < minDistance )
		{
			minIndex = i;
			minDistance = distance;
		}
	}
	return minIndex;
}

void CalculateDelaunayTriangles(cv::Rect rect, std::vector<cv::Point2f> &points, std::vector< std::vector<int> > &delaunayTri)
{
	// Create an instance of Subdiv2D
	cv::Subdiv2D subdiv(rect);

	// Insert points into subdiv
	for( std::vector<cv::Point2f>::iterator it = points.begin(); it != points.end(); it++)
	  subdiv.insert(*it);

	// Get Delaunay triangulation
	std::vector<cv::Vec6f> triangleList;
	subdiv.getTriangleList(triangleList);

	// Variable to store a triangle ( 3 points )
	std::vector<cv::Point2f> pt(3);

	// Variable to store a triangle as indices from list of points
	std::vector<int> ind(3);

	for( size_t i = 0; i < triangleList.size(); i++ )
	{
	  // The triangle returned by getTriangleList is
	  // a list of 6 coordinates of the 3 points in
	  // x1, y1, x2, y2, x3, y3 format.
	  cv::Vec6f t = triangleList[i];

	  // Store triangle as a vector of three points
	  pt[0] = cv::Point2f(t[0], t[1]);
	  pt[1] = cv::Point2f(t[2], t[3]);
	  pt[2] = cv::Point2f(t[4], t[5]);


	  if ( rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2]))
	  {
		// Find the index of each vertex in the points list
		for(int j = 0; j < 3; j++)
		{
		  ind[j] = FindIndex(points, pt[j]);
		}
		// Store triangulation as a list of indices
		delaunayTri.push_back(ind);
	  }
	}

}

void ApplyAffineTransform(cv::Mat &warpImage, cv::Mat &src, std::vector<cv::Point2f> &srcTri, std::vector<cv::Point2f> &dstTri)
{
  // Given a pair of triangles, find the affine transform.
  cv::Mat warpMat = cv::getAffineTransform( srcTri, dstTri );

  // Apply the Affine Transform just found to the src image
  cv::warpAffine( src, warpImage, warpMat, warpImage.size(), cv::INTER_LINEAR, cv::BORDER_REFLECT_101);
}

void WarpTriangle(cv::Mat &img1, cv::Mat &img2, std::vector<cv::Point2f> t1, std::vector<cv::Point2f> t2)
{
  // Find bounding rectangle for each triangle
  cv::Rect r1 = boundingRect(t1);
  cv::Rect r2 = boundingRect(t2);
  // Offset points by left top corner of the respective rectangles
  std::vector<cv::Point2f> t1Rect, t2Rect;
  std::vector<cv::Point> t2RectInt;
  for(int i = 0; i < 3; i++)
  {
	//tRect.push_back( Point2f( t[i].x - r.x, t[i].y -  r.y) );
	t2RectInt.push_back( cv::Point((int)(t2[i].x - r2.x), (int)(t2[i].y - r2.y)) ); // for fillConvexPoly

	t1Rect.push_back( cv::Point2f( t1[i].x - r1.x, t1[i].y -  r1.y) );
	t2Rect.push_back( cv::Point2f( t2[i].x - r2.x, t2[i].y - r2.y) );
  }

  // Get mask by filling triangle
  cv::Mat mask = cv::Mat::zeros(r2.height, r2.width, CV_32FC3);
  fillConvexPoly(mask, t2RectInt, cv::Scalar(1.0, 1.0, 1.0), 16, 0);

  // Apply warpImage to small rectangular patches
  cv::Mat img1Rect, img2Rect;
  img1(r1).copyTo(img1Rect);

  cv::Mat warpImage = cv::Mat::zeros(r2.height, r2.width, img1Rect.type());

  ApplyAffineTransform(warpImage, img1Rect, t1Rect, t2Rect);

  // Copy triangular region of the rectangular patch to the output image
  cv::multiply(warpImage,mask, warpImage);
  cv::multiply(img2(r2), cv::Scalar(1.0,1.0,1.0) - mask, img2(r2));
  img2(r2) = img2(r2) + warpImage;
}

bool RectAreaComparator(dlib::rectangle &r1, dlib::rectangle &r2)
{
	return r1.area() < r2.area();
}

void WarpImage(cv::Mat &imgIn, cv::Mat &imgOut, std::vector<cv::Point2f> &pointsIn, std::vector<cv::Point2f> &pointsOut, std::vector< std::vector<int> > &delaunayTri, bool useOutputImageSize)
{
  // Specify the output image the same size and type as the input image.
  cv::Size size = imgIn.size();
  if(!useOutputImageSize)
  {
	imgOut = cv::Mat::zeros(size, imgIn.type());
  }

  // Warp each input triangle to output triangle.
  // The triangulation is specified by delaunayTri
  for(size_t j = 0; j < delaunayTri.size(); j++)
  {
	// Input and output points corresponding to jth triangle
	std::vector<cv::Point2f> tin, tout;

	for(int k = 0; k < 3; k++)
	{
	  // Extract a vertex of input triangle
	  cv::Point2f pIn = pointsIn[delaunayTri[j][k]];
	  // Make sure the vertex is inside the image.
	  ConstrainPoint(pIn, size);

	  // Extract a vertex of the output triangle
	  cv::Point2f pOut = pointsOut[delaunayTri[j][k]];

	  // Make sure the vertex is inside the image.
	  if(useOutputImageSize)
	  {
		ConstrainPoint(pOut,imgOut.size());
	  }
	  else
	  {
	   ConstrainPoint(pOut,size);
	  }

	  // Push the input vertex into input triangle
	  tin.push_back(pIn);
	  // Push the output vertex into output triangle
	  tout.push_back(pOut);
	}
	// Warp pixels inside input triangle to output triangle.
	WarpTriangle(imgIn, imgOut, tin, tout);
  }
}

void DrawDelaunayTriangles(cv::Mat &img, std::vector<cv::Point2f> &points, std::vector< std::vector<int> > &dt)
{
	const auto type = img.type();
	img.convertTo(img, CV_32F);
	// Apply affine transformation to Delaunay triangles
	for(size_t i = 0; i < dt.size(); i++)
	{
		std::vector<cv::Point> t;
		// Get points for img1, img2 corresponding to the triangles
		for(size_t j = 0; j < 3; j++)
			t.push_back({int(points[dt[i][j]].x), int(points[dt[i][j]].y)});

		cv::line(img, t[0], t[1], cv::Scalar(0, 255, 0), 1);
		cv::line(img, t[1], t[2], cv::Scalar(0, 255, 0), 1);
		cv::line(img, t[0], t[2], cv::Scalar(0, 255, 0), 1);
	}
	img.convertTo(img, type);
}

}}

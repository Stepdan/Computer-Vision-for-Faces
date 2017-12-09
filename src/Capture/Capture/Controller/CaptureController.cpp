#include "opencv2/opencv.hpp"

#include "Core/DataImage/CvDataImage.h"
#include "Core/Utils/ImageUtils.h"

#include "CaptureController.h"

namespace Capture {

CaptureController::CaptureController()
{

}

void CaptureController::Start()
{
	m_needCapture = true;

	m_captureThread = std::make_unique<std::thread>([this]()
	{
		cv::VideoCapture cvCapture(0);
		if(!cvCapture.isOpened())
			m_needCapture = false;

		while(m_needCapture)
		{
			cv::Mat cvFrame;
			cvCapture.read(cvFrame);

			if(cvFrame.empty())
			{
				m_needCapture = false;
				break;
			}

			emit frameCaptured(Core::Utils::cvMat2QImage(cvFrame));
		}

		cvCapture.release();
	});

	m_captureThread->detach();
}

void CaptureController::Stop()
{
	m_needCapture = false;
}

void CaptureController::AddEffect(const Proc::BaseSettings & settings)
{

}

}

#include <ctime>

#include "opencv2/opencv.hpp"

#include "Core/DataImage/CvDataImage.h"
#include "Core/Utils/ImageUtils.h"

#include "Proc/Effects/Factory/EffectsFactory.h"

#include "CaptureController.h"

using namespace Proc::Interfaces;

namespace Capture {

CaptureController::CaptureController()
{
}

void CaptureController::Start()
{
	m_isCaptured = true;

	m_captureThread = std::make_unique<std::thread>([this]()
	{
		int frameCount = 0;
		time_t startTime, endTime;

		cv::VideoCapture cvCapture(0);
		if(!cvCapture.isOpened())
			m_isCaptured = false;

		std::time(&startTime);
		while(m_isCaptured)
		{
			cv::Mat cvFrame;
			cvCapture.read(cvFrame);

			if(cvFrame.empty())
			{
				m_isCaptured = false;
				break;
			}

			++frameCount;
			std::time(&endTime);
			if(std::difftime(endTime, startTime) > 1)
			{
				m_captureInfo.width = cvFrame.cols;
				m_captureInfo.height = cvFrame.rows;
				m_captureInfo.fps = frameCount / std::difftime(endTime, startTime);
				startTime = endTime;
				frameCount = 0;

				emit captureInfoChanged(m_captureInfo);
			}

			cv::Mat frameWithEffects;
			for(const auto & effect : m_effectsOne)
			{
				effect->Apply(cvFrame, frameWithEffects);
				cvFrame = frameWithEffects;
			}

			emit frameCaptured(Core::Utils::cvMat2QImage(cvFrame));
		}

		cvCapture.release();
	});

	m_captureThread->detach();
}

void CaptureController::Stop()
{
	m_isCaptured = false;
}

void CaptureController::AddEffect(const Proc::BaseSettings & settings)
{
	auto it = std::find_if(m_effectsOne.cbegin(), m_effectsOne.cend(),
					[&settings](const SharedPtr<IEffectOne>& e) { return e->GetBaseSettings().GetSettingsID() == settings.GetSettingsID(); });

	if(it != m_effectsOne.cend())
	{
		(*it)->SetBaseSettings(settings);
	}
	else
	{
		auto effect = Proc::EffectsFactory::Instance().CreateEffectOne(settings.GetSettingsID());
		effect->SetBaseSettings(settings);

		m_effectsOne.push_back(effect);
	}
}

}

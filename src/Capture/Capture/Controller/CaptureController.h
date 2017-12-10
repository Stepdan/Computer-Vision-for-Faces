#pragma once

#include <thread>
#include <vector>

#include <QObject>
#include <QImage>

#include "Types/Pointers.h"
#include "Proc/Interfaces/IEffectOne.h"
#include "Proc/Settings/BaseSettings.h"

#include "Capture/CaptureInfo.h"

namespace Capture {

class CaptureController : public QObject
{
	Q_OBJECT
public:
	explicit CaptureController();
	~CaptureController() = default;

	void Start();
	void Stop();

	void AddEffect(const Proc::BaseSettings &);

signals:
	void frameCaptured(const QImage &);
	void captureInfoChanged(const Capture::CaptureInfo &);

private:
	UniquePtr<std::thread> m_captureThread;
	bool m_needCapture = false;

	CaptureInfo m_captureInfo;

	std::vector<SharedPtr<Proc::Interfaces::IEffectOne>> m_effectsOne;
};

}

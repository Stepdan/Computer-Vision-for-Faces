#pragma once

#include <thread>

#include <QObject>
#include <QImage>

#include "Types/Pointers.h"
#include "Proc/Settings/BaseSettings.h"

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

private:
	UniquePtr<std::thread> m_captureThread;
	bool m_needCapture = false;
};

}

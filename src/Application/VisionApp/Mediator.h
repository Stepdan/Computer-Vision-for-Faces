#pragma once

#include <QObject>
#include <QSettings>

#include "Types/Pointers.h"
#include "Helpers/EffectHelper.h"
#include "UI/MainWindow.h"

namespace VisionApp {

class Mediator : public QObject
{
	Q_OBJECT

public:
	Mediator(const SharedPtr<MainWindow> & mainWindow);
	~Mediator() = default;

private slots:
	void OnLoadImage();
	void OnSaveImage();
	void OnApplyEffect();

private:
	SharedPtr<MainWindow> m_mainWindow;
	UniquePtr<QSettings> m_settings;

	UniquePtr<EffectHelper> m_effectHelper;
};

}

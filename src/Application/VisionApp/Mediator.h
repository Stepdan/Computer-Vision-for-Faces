#pragma once

#include <QObject>
#include <QSettings>

#include "Types/Pointers.h"
#include "Helpers/EffectHelper.h"
#include "Helpers/ImageHelper.h"
#include "Helpers/UndoHelper.h"
#include "UI/MainWindow/MainWindow.h"

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
	void OnUndo();
	void OnRedo();
	void OnReset();
	void OnCompare();

	void OnApplyEffect(const SharedPtr<Proc::BaseSettings>&);

private:
	SharedPtr<MainWindow> m_mainWindow;
	UniquePtr<QSettings> m_settings;

	SharedPtr<ImageHelper> m_imageHelper;

	UniquePtr<EffectHelper> m_effectHelper;
	UniquePtr<UndoHelper> m_undoHelper;
};

}

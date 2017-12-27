#pragma once

#include <QWidget>
#include <QPointer>

#include "UI/EffectsPanel/EffectsPanel.h"
#include "UI/CapturePanel/CapturePanel.h"
#include "UI/TrainingPanel/TrainingPanel.h"

namespace Ui {
class SettingsPanel;
}

class SettingsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsPanel(QWidget *parent = 0);
	~SettingsPanel();

signals:
	void click();

private slots:
	void OnEffectsClicked();
	void OnCaptureClicked();
	void OnTrainingClicked();

private:
	Ui::SettingsPanel *ui;

	QPointer<EffectsPanel> m_effectsPanel;
	QPointer<CapturePanel> m_capturePanel;
	QPointer<TrainingPanel> m_trainingPanel;
};

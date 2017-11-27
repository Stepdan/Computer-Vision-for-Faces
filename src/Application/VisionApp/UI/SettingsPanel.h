#pragma once

#include <QWidget>
#include <QPointer>

#include "EffectsPanel/EffectsPanel.h"

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

private:
	Ui::SettingsPanel *ui;

	QPointer<EffectsPanel> m_effectsPanel;
};

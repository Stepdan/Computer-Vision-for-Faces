#pragma once

#include <QWidget>

#include "Types/Pointers.h"

namespace Ui {
class EffectsPanel;
}

namespace Proc {
class BaseSettings;
}

class EffectsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit EffectsPanel(QWidget *parent = 0);
	~EffectsPanel();

signals:
	void effectApplyed(const SharedPtr<Proc::BaseSettings>&);

private:
	void OnEffectChanged(int index);

private:
	Ui::EffectsPanel *ui;

	SharedPtr<Proc::BaseSettings> m_settings;
};

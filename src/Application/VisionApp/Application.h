#pragma once

#include <QApplication>

namespace VisionApp {

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);

	void SetStyle();

};

}

/**
* @brief Получение указателя на синглтон Application
**/

#define visionApp (static_cast<VisionApp::Application*>(QApplication::instance()))

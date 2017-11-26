#include "Application.h"

#include <QFile>
#include <QString>

namespace
{
const QString APP_STYLE_FILE = ":/style.qss";
}

namespace VisionApp {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{
}

void Application::SetStyle()
{
	QFile styleFile(APP_STYLE_FILE);
	styleFile.open(QIODevice::ReadOnly);
	QString styleSheet = styleFile.readAll();
	setStyleSheet(styleSheet);
}

}

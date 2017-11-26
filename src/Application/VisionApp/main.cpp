#include "Types/Pointers.h"

#include "Application.h"
#include "Mediator.h"

#include "UI/MainWindow.h"

int main(int argc, char *argv[])
{
	VisionApp::Application application(argc, argv);

	SharedPtr<MainWindow> mainForm(new MainWindow());
	VisionApp::Mediator mediator(mainForm);

	visionApp->installEventFilter(&mediator);
	visionApp->installEventFilter(mainForm.get());

	//visionApp->SetStyle();

	mainForm->show();

	return application.exec();
}

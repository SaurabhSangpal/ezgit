#include <git2.h>
#include <qapplication.h>

#include "ui/MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow   mainWindow;
	return app.exec();
}
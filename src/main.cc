#include <git2.h>
#include <QApplication>

#include "ui/MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow   mainWindow;
	return app.exec();
}
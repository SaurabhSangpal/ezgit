#include <git2.h>
#include <qapplication.h>

#include "ui/MainWindow.h"

int main(int argc, char** argv) {
	git_libgit2_init();
	QApplication app(argc, argv);
	MainWindow   mainWindow;
	return app.exec();
	git_libgit2_shutdown();
}
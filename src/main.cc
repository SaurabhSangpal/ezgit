#include <git2.h>
#include <qapplication.h>
#include "ui/MainWindow.h"

int main(int argc, char** argv) {
	QApplication   app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
	/*
	git_libgit2_init();
	// Testing
	git_repository* repo;

	int err = git_repository_init(&repo, "Z:\\testrepo", 0);
	if (err == 0) {
	}

	git_libgit2_shutdown();
	return 0;
	*/
}
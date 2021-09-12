#include "MainWindow.h"

#include <qlayout.h>

#include "./ui_MainWindow.h"
#include "RepoViewerWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setWindowTitle("Ez Git");

	// auto* repoViewerWidget = new RepoViewerWidget(this);
	// mainWidget	       = repoViewerWidget;

	show();
}

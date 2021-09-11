#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <qdesktopwidget.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
}

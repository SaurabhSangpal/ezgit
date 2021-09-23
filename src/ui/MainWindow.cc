#include "MainWindow.h"

#include <qaction.h>
#include <qfiledialog.h>
#include <qlayout.h>
#include <qmessagebox.h>

#include "../git_wrapper/Repository.h"
#include "./ui_MainWindow.h"
#include "CloneDialog.h"
#include "RepoViewerWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setWindowTitle("Ez Git");

	ui->actionCreate_Repository->setShortcuts(QKeySequence::New);
	ui->actionOpen_Repository->setShortcuts(QKeySequence::Open);
	ui->actionExit->setShortcuts(QKeySequence::Quit);

	connect(ui->actionCreate_Repository, &QAction::triggered, this,
		&MainWindow::InitRepository);
	connect(ui->actionOpen_Repository, &QAction::triggered, this, &MainWindow::OpenRepository);
	connect(ui->actionClone_Repository, &QAction::triggered, this,
		&MainWindow::CloneRepository);
	connect(ui->actionExit, &QAction::triggered, this, []() { std::exit(0); });

	auto* repoViewerWidget = new RepoViewerWidget(this);
	setCentralWidget(repoViewerWidget);
	// mainWidget	       = repoViewerWidget;

	show();
}

void MainWindow::OpenRepository() noexcept {
	QString dir = QFileDialog::getExistingDirectory(
	    this, tr("Select Git Repository"), "/home",
	    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	auto path = dir.toStdString();
	if (path.empty()) return;

	git::Repository repo;
	if (repo.Open(path.c_str())) {
	} else {
		QMessageBox::warning(this, "Failure", "Failed to open repository.",
				     QMessageBox::StandardButton::Ok);
	}
}

void MainWindow::InitRepository() noexcept {
	QString dir = QFileDialog::getExistingDirectory(
	    this, tr("Select Git Repository"), "/home",
	    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	auto path = dir.toStdString();
	if (path.empty()) return;

	git::Repository repo;
	if (repo.Create(path.c_str())) {
		QMessageBox::information(this, "Success", "Successfully created repository.",
					 QMessageBox::StandardButton::Ok);
	} else {
		QMessageBox::warning(this, "Failure", "Failed to create repository.",
				     QMessageBox::StandardButton::Ok);
	}
}

void MainWindow::CloneRepository() noexcept {
	auto* dialog = new CloneDialog(this);
	dialog->exec();
}

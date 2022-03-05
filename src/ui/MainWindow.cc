#include "MainWindow.h"

#include <git2.h>

#include <QAction>
#include <QFileDialog>
#include <QLayout>
#include <QMessageBox>

#include "../git_wrapper/Repository.h"
#include "./ui_MainWindow.h"
#include "CloneDialog.h"
#include "RepoViewerWidget.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	git_libgit2_init();

	ui->setupUi(this);
	setWindowTitle("Ez Git");

	ui->actionCreate_Repository->setShortcuts(QKeySequence::New);
	ui->actionOpen_Repository->setShortcuts(QKeySequence::Open);
	ui->actionClone_Repository->setShortcut(QKeySequence("Ctrl+Shift+O"));
	ui->actionOptions->setShortcut(QKeySequence("Ctrl+,"));
	ui->actionExit->setShortcuts(QKeySequence::Quit);
	ui->actionAbout->setShortcut(QKeySequence("?"));

	connect(ui->actionCreate_Repository, &QAction::triggered, this,
		&MainWindow::InitRepository);
	connect(ui->actionOpen_Repository, &QAction::triggered, this, &MainWindow::OpenRepository);
	connect(ui->actionClone_Repository, &QAction::triggered, this,
		&MainWindow::CloneRepository);
	connect(ui->actionExit, &QAction::triggered, this, []() { std::exit(0); });
	connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::ShowAbout);

	show();
}

MainWindow::~MainWindow() noexcept { git_libgit2_shutdown(); }

void MainWindow::OpenRepository() noexcept {
	QString dir = QFileDialog::getExistingDirectory(
	    this, tr("Select Git Repository"), "/home",
	    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty()) return;

	auto repo = std::make_shared<git::Repository>();
	if (repo->Open((char*)dir.toLocal8Bit().data())) {
		repository = repo;
		InitializeRepoViewerWidget();
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

	auto repo = std::make_shared<git::Repository>();
	if (repo->Create(path.c_str())) {
		repository = repo;
		InitializeRepoViewerWidget();
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

void MainWindow::ShowAbout() noexcept {
	QMessageBox::about(this, "About",
			   "Created by Saurabh Sangpal\n2021-2022 All Rights Reserved.");
}

void MainWindow::InitializeRepoViewerWidget() noexcept {
	auto* repoViewerWidget = new RepoViewerWidget(*repository, this);
	setCentralWidget(repoViewerWidget);
}

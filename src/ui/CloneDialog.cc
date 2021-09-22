#include "CloneDialog.h"

#include <qfiledialog.h>
#include <qmessagebox.h>

#include "../git_wrapper/Repository.h"
#include "./ui_CloneDialog.h"

CloneDialog::CloneDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CloneDialog) {
	ui->setupUi(this);

	connect(ui->btnBrowseDestination, &QPushButton::clicked, this,
		&CloneDialog::BrowseForDestinationFolder);
	connect(ui->btnClone, &QPushButton::clicked, this, &CloneDialog::CloneRepo);
	connect(ui->btnCancel, &QPushButton::clicked, this, &CloneDialog::reject);
}

void CloneDialog::BrowseForDestinationFolder() noexcept {
	QString dir = QFileDialog::getExistingDirectory(
	    this, tr("Select Destination"), "/home",
	    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (dir.toStdString().empty()) {
		return;
	}

	ui->leDestination->setText(dir);
}

void CloneDialog::CloneRepo() noexcept {
	auto url  = ui->leRepoUrl->text();
	auto dest = ui->leDestination->text();

	if (url.toStdString().empty() || dest.toStdString().empty()) {
		const char* errUrl =
		    "Failed to clone the repository because the provided URL is empty!";
		const char* errDest =
		    "Failed to clone the repository because the provided destination is empty!";
		auto errorText = url.toStdString().empty() ? errUrl : errDest;
		QMessageBox::warning(this, "Failed to clone", errorText);
		return;
	}

	git::Repository repo;
	if (!repo.Clone(url.toStdString().c_str(), dest.toStdString().c_str())) {
		QMessageBox::warning(this, "Failed to clone", "Failed to clone the repository!");
	}
	else {
		// TODO: Open the repo in UI.
		accept();
	}
}

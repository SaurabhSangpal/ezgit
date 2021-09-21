#include "CloneDialog.h"

#include <qfiledialog.h>

#include "./ui_CloneDialog.h"

CloneDialog::CloneDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CloneDialog) {
	ui->setupUi(this);

	connect(ui->btnBrowseDestination, &QPushButton::clicked, this,
		&CloneDialog::BrowseForDestinationFolder);
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

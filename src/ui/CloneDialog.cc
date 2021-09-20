#include "CloneDialog.h"

#include "./ui_CloneDialog.h"

CloneDialog::CloneDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CloneDialog) {
	ui->setupUi(this);
}

#include "RepoViewerWidget.h"

#include "./ui_RepoViewerWidget.h"

RepoViewerWidget::RepoViewerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget) {
	ui->setupUi(this);
}

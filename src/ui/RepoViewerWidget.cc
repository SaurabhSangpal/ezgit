#include "RepoViewerWidget.h"

#include "../git_wrapper/Commit.h"
#include "./ui_RepoViewerWidget.h"
#include "AllCommits.h"

RepoViewerWidget::RepoViewerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget) {
	ui->setupUi(this);

	auto* gridLayout = new QVBoxLayout;
	ui->right->setLayout(gridLayout);
	auto* commits = new AllCommits(ui->right);
	gridLayout->addWidget(commits);
}

RepoViewerWidget::~RepoViewerWidget() noexcept { delete ui; }

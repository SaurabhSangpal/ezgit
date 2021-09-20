#include "RepoViewerWidget.h"

#include "../git_wrapper/Commit.h"
#include "./ui_RepoViewerWidget.h"
#include "Commit.h"
#include "qlayout.h"

RepoViewerWidget::RepoViewerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget) {
	ui->setupUi(this);

	git::Commit commit;
	commit.Setup("Add generic comment", "Saurabh Sangpal", "asch23kcks", "18 Sep 2021 18:30");

	auto* layout = new QVBoxLayout;
	ui->commitsScrollAreaContent->setLayout(layout);

	for (int i = 0; i < 10; i++) {
		auto* uiCommit = new Commit(ui->commitsScrollAreaContent);
		uiCommit->Setup(commit);
		layout->addWidget(uiCommit);
	}
	ui->commitsScrollArea->setWidget(ui->commitsScrollAreaContent);
}

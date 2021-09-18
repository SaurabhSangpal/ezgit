#include "RepoViewerWidget.h"

#include "../git_wrapper/Commit.h"
#include "./ui_RepoViewerWidget.h"
#include "Commit.h"

RepoViewerWidget::RepoViewerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget) {
	ui->setupUi(this);

	git::Commit commit;
	commit.Setup("Add generic comment", "Saurabh Sangpal", "asch23kcks", "18 Sep 2021 18:30");

	auto* uiCommit = new Commit(ui->commitsScrollArea);
	uiCommit->Setup(commit);
}

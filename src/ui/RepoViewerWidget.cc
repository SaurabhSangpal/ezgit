#include "RepoViewerWidget.h"

#include <git2.h>

#include "../git_wrapper/Commit.h"
#include "../git_wrapper/Repository.h"
#include "./ui_RepoViewerWidget.h"
#include "AllCommits.h"

RepoViewerWidget::RepoViewerWidget(git::Repository& repo, QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget), repo(repo) {
	ui->setupUi(this);
	allCommitsWidget = yourChangesWidget = nullptr;

	ui->lblRepoName->setText(repo.GetRepoLocation().c_str());

	connect(ui->btnYourChanges, &QPushButton::clicked, this,
		&RepoViewerWidget::ActivateYourChangesUI);
	connect(ui->btnAllCommits, &QPushButton::clicked, this,
		&RepoViewerWidget::ActivateAllCommitsUI);

	FetchRemoteList();
	ActivateAllCommitsUI();
}

RepoViewerWidget::~RepoViewerWidget() noexcept { delete ui; }

Remotes RepoViewerWidget::GetRemotes() const noexcept { return remotes; }

bool RepoViewerWidget::FetchRemoteList() noexcept {
	git_strarray out = {nullptr};
	if (git_remote_list(&out, repo.GetRepository()) != 0) {
		for (int i = 0; i < out.count; i++) {
			git_remote* remote = {nullptr};
			if (git_remote_lookup(&remote, repo.GetRepository(), out.strings[i]) != 0)
				continue;

			auto r = std::make_shared<git::Remote>(git::Remote(remote));
			remotes.push_back(r);
			git_remote_free(remote);
		}
		git_strarray_free(&out);
		return true;
	}
	return false;
}

void RepoViewerWidget::DestroyActiveWidget() noexcept {
	if (allCommitsWidget != nullptr && allCommitsWidget->isEnabled()) {
		allCommitsWidget->hide();
	}
	if (yourChangesWidget != nullptr && yourChangesWidget->isEnabled()) {
		yourChangesWidget->hide();
	}
}

void RepoViewerWidget::ActivateYourChangesUI() noexcept {
	DestroyActiveWidget();
	// TODO: Implement activate your changes UI.
}

void RepoViewerWidget::ActivateAllCommitsUI() noexcept {
	DestroyActiveWidget();

	if (allCommitsWidget == nullptr) {
		auto* layout  = FetchOrCreateLayoutOnRight();
		auto* commits = new AllCommits(repo, ui->right);
		layout->addWidget(commits);
		activeWidgetDestroyed = false;
		allCommitsWidget      = commits;
	} else {
		allCommitsWidget->show();
	}
}

QLayout* RepoViewerWidget::FetchOrCreateLayoutOnRight() noexcept {
	QLayout* layout = nullptr;
	if (ui->right->layout() != nullptr) {
		layout = ui->right->layout();
	} else {
		layout = new QVBoxLayout;
		layout->setMargin(0);
		ui->right->setLayout(layout);
	}
	return layout;
}

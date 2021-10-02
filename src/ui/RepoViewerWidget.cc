#include "RepoViewerWidget.h"

#include <git2.h>

#include "../git_wrapper/Commit.h"
#include "../git_wrapper/Repository.h"
#include "./ui_RepoViewerWidget.h"
#include "AllCommits.h"

RepoViewerWidget::RepoViewerWidget(git::Repository& repo, QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget), repo(repo) {
	ui->setupUi(this);
	activeWidget = nullptr;

	connect(ui->btnYourChanges, &QPushButton::clicked, this,
		&RepoViewerWidget::ActivateYourChangesUI);
	connect(ui->btnAllCommits, &QPushButton::clicked, this,
		&RepoViewerWidget::ActivateAllCommitsUI);
}

RepoViewerWidget::~RepoViewerWidget() noexcept { delete ui; }

std::vector<std::shared_ptr<git::Remote>> RepoViewerWidget::GetRemotes() const noexcept {
	return remotes;
}

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

QLayout* GetActiveLayoutOnRightElement(Ui::RepoViewerWidget* ui);

void RepoViewerWidget::ActivateYourChangesUI() noexcept {
	if (activeWidget != nullptr) activeWidget->deleteLater();
	// TODO: Implement activate your changes UI.
}

void RepoViewerWidget::ActivateAllCommitsUI() noexcept {
	// TODO: Check why the program crashes here?
//	if (activeWidget != nullptr) activeWidget->deleteLater();
	auto* layout  = GetActiveLayoutOnRightElement(ui);
	auto* commits = new AllCommits(ui->right);
	layout->addWidget(commits);

	activeWidget = commits;
}

//! Helper method to get the layout on ui->right
QLayout* GetActiveLayoutOnRightElement(Ui::RepoViewerWidget* ui) {
	QLayout* layout = nullptr;
	if (ui->right->layout() != nullptr) {
		layout = ui->right->layout();
	} else {
		layout = new QVBoxLayout;
		ui->right->setLayout(layout);
	}
	return layout;
}

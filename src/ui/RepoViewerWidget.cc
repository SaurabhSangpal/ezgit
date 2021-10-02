#include "RepoViewerWidget.h"

#include <git2.h>

#include "../git_wrapper/Commit.h"
#include "../git_wrapper/Repository.h"
#include "./ui_RepoViewerWidget.h"
#include "AllCommits.h"

RepoViewerWidget::RepoViewerWidget(git::Repository& repo, QWidget* parent)
    : QWidget(parent), ui(new Ui::RepoViewerWidget), repo(repo) {
	ui->setupUi(this);

	auto* gridLayout = new QVBoxLayout;
	ui->right->setLayout(gridLayout);
	auto* commits = new AllCommits(ui->right);
	gridLayout->addWidget(commits);
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

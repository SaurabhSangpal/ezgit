#pragma once
#include <qwidget.h>

#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class RepoViewerWidget;
}
QT_END_NAMESPACE

namespace git {
class Repository;
class Remote;
}  // namespace git

class RepoViewerWidget : public QWidget {
    public:
	explicit RepoViewerWidget(git::Repository& repo, QWidget* parent = nullptr);
	~RepoViewerWidget() noexcept override;

	[[nodiscard]] std::vector<std::shared_ptr<git::Remote>> GetRemotes() const noexcept;

    private:
	//! Executes git_remote_list and stores the remotes in remotes.
	bool FetchRemoteList() noexcept;

	Ui::RepoViewerWidget* ui;
	git::Repository&      repo;
	// NOTE: Use git_remote_list to get a list of available remotes.
	std::vector<std::shared_ptr<git::Remote>> remotes;
};
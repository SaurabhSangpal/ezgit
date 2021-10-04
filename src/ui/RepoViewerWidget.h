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

typedef std::vector<std::shared_ptr<git::Remote>> Remotes;

class RepoViewerWidget : public QWidget {
    public:
	explicit RepoViewerWidget(git::Repository& repo, QWidget* parent = nullptr);
	~RepoViewerWidget() noexcept override;

	[[nodiscard]] Remotes GetRemotes() const noexcept;

    private:
	//! Executes git_remote_list and stores the remotes in remotes.
	bool FetchRemoteList() noexcept;

	void DestroyActiveWidget() noexcept;
	void ActivateYourChangesUI() noexcept;
	void ActivateAllCommitsUI() noexcept;

	//! If a layout is present on ui->right, then fetches it. Otherwise creates and assigns
	//! a layout to ui->right and returns that.
	QLayout* FetchOrCreateLayoutOnRight() noexcept;

	bool		      activeWidgetDestroyed = false;
	Ui::RepoViewerWidget* ui;
	git::Repository&      repo;
	Remotes		      remotes;
	QWidget*	      activeWidget;
};
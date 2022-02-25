#pragma once

#include <QWidget>
#include <future>
#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class AllCommits;
}
QT_END_NAMESPACE

namespace git {
class Commit;
class Repository;
}  // namespace git

class Commit;

typedef std::vector<std::shared_ptr<Commit>> Commits;
typedef std::vector<git::Commit>*	     Log;

struct git_revwalk;

class AllCommits : public QWidget {
	Q_OBJECT

    public:
	explicit AllCommits(git::Repository& repo, QWidget* parent = nullptr);
	~AllCommits() override;

	void Fetch() noexcept;

    private:
	Log  FetchLog() noexcept;
	void FetchLogAsync(std::promise<Log>&& promise) noexcept;

	git_revwalk* InitializeRevWalk() noexcept;
	git_revwalk* FetchLog(git_revwalk* revWalk, int logCount, Log log) noexcept;

	void AddCommit(const git::Commit& commit) noexcept;
	void DisplayAllCommits(const Log commitsVec) noexcept;

	Ui::AllCommits*	 ui;
	Commits		 commits;
	git::Repository& repo;
};

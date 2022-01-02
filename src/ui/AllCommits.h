#pragma once

#include <QWidget>
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

class AllCommits : public QWidget {
	Q_OBJECT

    public:
	explicit AllCommits(git::Repository& repo, QWidget* parent = nullptr);
	~AllCommits() override;

	void Fetch() noexcept;

    private:
	std::vector<git::Commit> FetchLog() noexcept;
	void			 AddCommit(const git::Commit& commit) noexcept;
	void DisplayAllCommits(const std::vector<git::Commit>& commitsVec) noexcept;

	Ui::AllCommits*	 ui;
	Commits		 commits;
	git::Repository& repo;
};

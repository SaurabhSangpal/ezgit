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

	void AddCommit(const git::Commit& commit) noexcept;

    private:
	void FetchLog() noexcept;

	Ui::AllCommits*	 ui;
	Commits		 commits;
	git::Repository& repo;
};

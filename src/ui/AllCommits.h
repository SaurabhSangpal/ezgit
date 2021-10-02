#pragma once

#include <QWidget>
#include <vector>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class AllCommits;
}
QT_END_NAMESPACE

namespace git {
class Commit;
}

class Commit;

class AllCommits : public QWidget {
	Q_OBJECT

    public:
	explicit AllCommits(QWidget* parent = nullptr);
	~AllCommits() override;

	void AddCommit(const git::Commit& commit) noexcept;

    private:
	Ui::AllCommits* ui;
	std::vector<std::shared_ptr<Commit>> commits;
};

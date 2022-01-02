#pragma once

#include <qwidget.h>

namespace git {
class Repository;
}

class QFrame;
struct git_index;

class YourChanges : public QWidget {
	Q_OBJECT
    public:
	explicit YourChanges(git::Repository& repo, QWidget* parent = nullptr);
	~YourChanges() noexcept override;

    private:
	QFrame *staged, *unstaged;
	git_index* index;
};

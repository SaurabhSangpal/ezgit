#pragma once

#include <qwidget.h>

namespace git {
class Repository;
}

class QFrame;
struct git_status_list;

class YourChanges : public QWidget {
	Q_OBJECT
    public:
	explicit YourChanges(git::Repository& repo, QWidget* parent = nullptr);

    private:
	QFrame *staged, *unstaged;
	git_status_list* statusList;
};

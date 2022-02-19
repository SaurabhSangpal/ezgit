#pragma once

#include <QWidget>

namespace git {
class Repository;
}

class QFrame;
class QLabel;
class QPushButton;

class YourChanges : public QWidget {
	Q_OBJECT
    public:
	explicit YourChanges(git::Repository& repo, QWidget* parent = nullptr);

    private:
	QFrame *     staged, *unstaged;
	QLabel *     stagedLabel, *unstagedLabel;
	QPushButton *stageButton, *unstageButton;
};
